#include "BossZombie.h"
#include"BoxCollider.h"
#include "BattleController.h"
#include"BasePlant.h"
#include"ArmorZombie.h"
#include "GameStatics.h"



ABossZombie::ABossZombie()
{
	name = BossZombie;
	blood = 1000;
	speed *= 8;

	idle.Load("bossidle", 15, 1, 15, { -30,-25 });
	idle.SetInterval(0.1f);
	attack.Load("bossattack", 11, 1, 11, {-30,-25});
	attack.SetInterval(0.1f);

	ani->Insert("idle", idle);
	ani->Insert("attack", attack);
	ani->SetNode("idle");

	BehaviorTimeHandle.Bind(12.f, &ABossZombie::Behave, this, true);
}

void ABossZombie::Update()
{

	if (BlinkTimeHandle.GetDelay() > 0.25)
		renderer->SetTransparency(255);


	if (state == 0)BehaviorTimeHandle.Tick();
	

	if (box && state == 1) {
		AddPosition(speed);
		if (GetWorldPosition().x < 400) 
		{ 
			ani->SetNode("idle");
			state = 0; 
			BehaviorTimeHandle.ReSet();
			zombieNumPerRow[row]--;
			int num = RandEx(0, 4);
			SetPosition({650, num * 100.f +45});
			row = num;
			renderer->SetLayer(row + 2);
			zombieNumPerRow[row]++;
		}

		vector<Object*>buf = box->GetCollisions("Plant");
		if (!buf.empty()) {
			for (auto it = buf.begin(); it != buf.end(); ++it) {
				if (APlant* pPlant = Cast<APlant>(*it)) {
					if (pPlant->GetEnable())
					{
						pPlant->GetAttack(200);
					}
				}
			}
		}
	}


	if (blood <= 0)
	{
		Destroy(); zombieNumPerRow[row]--;
	}
}

void ABossZombie::Behave()
{
	int num = RandEx(0,10);

	if (num <= 3)
	{
		for (int i = 0; i < 5; i++) {
			AArmorZombie* buf = GameStatics::CreateObject<AArmorZombie>(Vector(800, i * 100 + 45));
			buf->row = i;
			buf->GetRenderer()->SetLayer(i + 2);
			zombieNumPerRow[i]++;
		}
	}
	else
	{
		ani->SetNode("attack");
		state = 1;//¹¥»÷Ä£Ê½
	}
}
