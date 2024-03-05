#include "Chomper.h"
#include "GameStatics.h"
#include "BoxCollider.h"
#include "Audio.h"
#include "BaseZombie.h"
#include "BattleController.h"


AChomper::AChomper()
{
	eatBox = GameStatics::ConstructComponent<BoxCollider>(Vector(15, 10));
	eatBox->SetAttachment(root);
	eatBox->SetType("EatScale");
	eatBox->SetSize(Vector(130, 60));

	renderer->SetPosition({5,-10});

	name = Chomper;
	type = Other;
	price = 150;

	temp.Load("chomper", 13, 1, 13);
	temp.SetInterval(0.1f);
	temp_1.Load("chomper_1", 9, 1, 9, {-1,-24});
	temp_1.SetInterval(0.1f);
	temp_2.Load("chomper_2", 6, 1, 6, {3,6});
	temp_2.SetInterval(0.1f);


	ani->Insert("idle", temp);
	ani->Insert("eat", temp_1);
	ani->Insert("chomp", temp_2);
	ani->SetNode("idle");

	ChompTimeHandle.Bind(40.f,&AChomper::EatUp,this);
}

void AChomper::Update()
{
	APlant::Update();

	if (!enabled)return;

	if (!state)
	{
		vector<Object*>buf = eatBox->GetCollisions("Zombie");

		if (!buf.empty()) {
			state = 1;
			ani->SetNode("eat");

			AudioSource bgm("res/sounds/bulletAttack/flowereat.mp3");
			player->Play(bgm);
		}
	}
	else if (state == 1)
	{
		if (ani->GetNode()->GetAni().index == 0 && eatFlag) {
			state = 2; ani->SetNode("chomp");
			eatFlag = false;
		}
		else if (ani->GetNode()->GetAni().index == 6 && !eatFlag)
		{
			eatFlag = true;
			vector<Object*>buf = eatBox->GetCollisions("Zombie");

			if (!buf.empty()) {
				for (auto it = buf.begin(); it != buf.end(); it++) {
					if (AZombie* pZombie = Cast<AZombie>(*it)) {
						if (pZombie->GetName() != BossZombie) { pZombie->Destroy(); zombieNumPerRow[row]--; break; }
						else { pZombie->GetAttack(3); state = 0; ani->SetNode("idle"); eatFlag = false; break; }
					}
				}
			}
			else
			{
				state = 0; ani->SetNode("idle"); eatFlag = false;
			}
		}
	}
	else if (state == 2)
	{
		ChompTimeHandle.Tick();
	}
	
}

void AChomper::EatUp()
{
	state = 0; ani->SetNode("idle");
}
