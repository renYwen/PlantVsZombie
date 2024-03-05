#include "CherryBomb.h"
#include "GameStatics.h"
#include "BoxCollider.h"
#include "Audio.h"
#include "BaseZombie.h"
#include "BattleController.h"
#include "Bomb.h"
#include "Camera.h"

ACherryBomb::ACherryBomb()
{
	name = CherryBomb;
	type = Disposable;
	price = 150;

	temp.Load("cherrybomb", 4, 4, 14,Vector(-15,-20));
	temp.SetInterval(0.06f);
	
	box->SetType("Bomb");
	box->AddPosition(Vector(-100, -100));
	box->SetSize(Vector(250, 250));

	ani->Insert("idle", temp);
	ani->SetNode("idle");
}

void ACherryBomb::Update()
{
	APlant::Update();

	
	if (ani->GetNode()->GetAni().index == 13) {
		AudioSource bgm("res/sounds/bulletAttack/bomb.mp3");
		player->Play(bgm);

		vector<Object*>buf = box->GetCollisions("Zombie");

		if (!buf.empty()) {
			for (auto it = buf.begin(); it != buf.end(); it++) {
				if (AZombie* pZombie = Cast<AZombie>(*it))pZombie->GetAttack(100,true);
			}
		}
		plants[column][row] = nullptr;
		Destroy();
		MainCamera->Shake(3);
		GameStatics::CreateObject<ABomb>(GetWorldPosition()-Vector(75,60));
	}
	
}
