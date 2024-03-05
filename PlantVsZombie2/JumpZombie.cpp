#include "JumpZombie.h"
#include"BoxCollider.h"
#include "BattleController.h"
#include"BasePlant.h"
#include"Audio.h"

AJumpZombie::AJumpZombie()
{
	name = JumpZombie;
	blood = 17;
	speed *=2;
	state = 3;//(3ÅÜ²½£¬4ÌøÔ¾)

	run.Load("jumprun", 6, 6, 36, Vector(-75, -20));
	run.SetInterval(0.03f);
	jump.Load("jumpjump", 11, 4, 42, Vector(-155, -25));
	jump.SetInterval(0.04f);
	walk.Load("jumpwalk", 5, 10, 44, Vector(0, -25));
	walk.SetInterval(0.06f);
	eat.Load("jumpeat", 3, 10, 27, Vector(0, -25));
	eat.SetInterval(0.04f);
	die.Load("jumpdie", 9, 1, 9, Vector(-50, -50));
	die.SetInterval(0.1f);

	run_1.Load("jumprun_1", 6, 6, 36, Vector(-75, -20));
	run_1.SetInterval(0.06f);
	jump_1.Load("jumpjump_1", 11, 4, 42, Vector(-155, -25));
	jump_1.SetInterval(0.08f);
	walk_1.Load("jumpwalk_1", 5, 10, 44, Vector(0, -25));
	walk_1.SetInterval(0.12f);
	eat_1.Load("jumpeat_1", 3, 10, 27, Vector(0, -25));
	eat_1.SetInterval(0.08f);
	die_1.Load("jumpdie_1", 9, 1, 9, Vector(-50, -50));
	die_1.SetInterval(0.2f);

	ani->Insert("run", run);
	ani->Insert("jump", jump);
	ani->Insert("walk", walk);
	ani->Insert("eat", eat);
	ani->Insert("die", die);
	ani->Insert("run_1", run_1);
	ani->Insert("jump_1", jump_1);
	ani->Insert("walk_1", walk_1);
	ani->Insert("eat_1", eat_1);
	ani->Insert("die_1", die_1);
	ani->SetNode("run");
}

void AJumpZombie::Update()
{
	AZombie::Update();

	if (state == 4)
	{
		shade->AddPosition({-0.33f*slowFlag,0});

		if (ani->GetNode()->GetAni().index == 41) {
			state = 0;
			box->SetOpen(true);
			AddPosition({-110,0});
			speed = { -0.06f,0 };
			shade->SetPosition({ 20, 105 });
			if (slowFlag == 2)ani->SetNode("walk");
			else ani->SetNode("walk_1");
		}
	}
}

void AJumpZombie::Judge()
{
	if (box) {

		vector<Object*>buf = box->GetCollisions("Plant");
		collisons.clear();

		if (!buf.empty()) {
			for (auto it = buf.begin(); it != buf.end(); ++it) {

				if (APlant* pPlant = Cast<APlant>(*it)) {
					if (pPlant->GetEnable())collisons.push_back(pPlant);
				}
			}
		}

		if (!collisons.empty()) {
			if (state == 3) {
				state = 4;
				speed = { 0,0 };
				box->SetOpen(false);
				if (slowFlag == 2)ani->SetNode("jump");
				else ani->SetNode("jump_1");
				AudioSource bgm("res/sounds/zombie/jump.mp3");
				player->Play(bgm);
			}
			else if (state == 0) {
				state = 1;
				if (slowFlag == 2)ani->SetNode("eat");
				else ani->SetNode("eat_1");
			}
		}
		else if (state == 1)
		{
			if (slowFlag == 2)ani->SetNode("walk");
			else ani->SetNode("walk_1");
			state = 0;
		}
	}
}
