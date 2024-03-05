#include"BaseZombie.h"
#include"GameStatics.h"
#include"BoxCollider.h"
#include"Audio.h"
#include"BasePlant.h"
#include "BattleController.h"
#include "Head.h"



AZombie::AZombie()
{
	ani = GameStatics::ConstructComponent<Animator>(Vector(0, 0));
	ani->SetAttachment(root);

	ash.Load("ash", 20, 1, 20, Vector(-3, -5));
	ash.SetInterval(0.1f);
	ani->Insert("ash", ash);

	shade = GameStatics::ConstructComponent<SpriteRenderer>(Vector(20, 105));
	shade->SetAttachment(root);
	shade->Load("bigShadow");
	shade->SetFetchAni(false);
	shade->SetTransparency(225);

	box = GameStatics::ConstructComponent<BoxCollider>(Vector(20, 30));
	box->SetAttachment(root);
	box->SetType("Zombie");
	box->SetSize(Vector(35, 85));
	box->SetColor(WHITE);
	
	player = GameStatics::ConstructComponent<AudioPlayer>(Vector(0, 0));
	player->SetAttachment(root);

	EatTimeHandle.Bind(0.6f, &AZombie::Eat, this, true);
	RecoverTimeHandle.Bind(5.f, &AZombie::Recover, this, true);
}

void AZombie::Update()
{
	Judge();

	if (state==0 || state > 2)AddPosition(speed*slowFlag);

	EatTimeHandle.Tick();

	if(slowFlag==1)RecoverTimeHandle.Tick();

	if (blood <= 0)
	{
		if (state != 2) {
			state = 2;
			box->Destruct(); box = nullptr;
			if (bAsh)ani->SetNode("ash");
			else {
				AHead* pHead = GameStatics::CreateObject<AHead>(GetWorldPosition() - Vector(0,5));
				if (slowFlag == 2)ani->SetNode("die");
				else { ani->SetNode("die_1"); pHead->Func(); pHead->GetRenderer()->SetLayer(row+3); }
				AudioSource bgm("res/sounds/zombieDie.mp3");
				player->Play(bgm);
			}
		}
		if (ani->GetNode()->GetAni().index >= ani->GetNode()->GetNum() - 1) {
			Destroy(); zombieNumPerRow[row]--;
		}
	}
		

	if (BlinkTimeHandle.GetDelay() > 0.25)
		renderer->SetTransparency(255);
}

void AZombie::Judge()
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
			if (state == 0) {
				state = 1;
				if(slowFlag==2)ani->SetNode("eat");
				else ani->SetNode("eat_1");
			}
		}
		else if(state == 1)
		{
			if (slowFlag == 2)ani->SetNode("walk");
			else ani->SetNode("walk_1");
			state = 0;
		}
	}
}

void AZombie::Eat()
{
	if (box && !collisons.empty()) {
		collisons[0]->GetAttack(1);
		AudioSource bgm;
		int flag = RandEx(0, 5);
		if (flag>1)bgm.Load("res/sounds/zombieEat/eat.mp3");
		else bgm.Load("res/sounds/zombieEat/eat_1.mp3");
		player->Play(bgm);
	}
}

void AZombie::GetAttack(int harm,bool boom)
{
	blood -= harm; renderer->SetTransparency(200); BlinkTimeHandle.ReSet();
	bAsh = blood <= 0 ? boom : false;
	if (name == BucketZombie && blood>10) {
		AudioSource bgm1;
		if (RandEx(0, 7) > 2)bgm1.Load("res/sounds/zombie/bucket.mp3");
		else bgm1.Load("res/sounds/zombie/bucket_1.mp3");
		player->Play(bgm1);
	}
	else if (name == HatZombie && blood>10)
	{
		AudioSource bgm2;
		if (RandEx(0, 7) > 3)bgm2.Load("res/sounds/zombie/hat.mp3");
		else bgm2.Load("res/sounds/zombie/hat_1.mp3");
		player->Play(bgm2);
	}
	else {
		AudioSource bgm("res/sounds/bulletAttack/pea.mp3");
		player->Play(bgm);
	}
}

void AZombie::Recover()
{
	slowFlag = 2;
	EatTimeHandle.SetDelay(0.6f);
	if (state == 0)ani->SetNode("walk");
	else if (state == 1)ani->SetNode("eat");
	else if (state == 3)ani->SetNode("run");
}

void AZombie::Freeze()
{
	RecoverTimeHandle.ReSet();
	if (slowFlag == 2) {
		if(state==0)ani->SetNode("walk_1");
		else if(state==1)ani->SetNode("eat_1");
		else if(state==3)ani->SetNode("run_1");
		slowFlag = 1;
		AudioSource bgm("res/sounds/bulletAttack/freeze.mp3");
		player->Play(bgm);
		EatTimeHandle.SetDelay(1.2f);
	}
}



