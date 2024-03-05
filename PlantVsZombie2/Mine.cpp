#include "Mine.h"
#include "GameStatics.h"
#include "BoxCollider.h"
#include "Audio.h"
#include "BaseZombie.h"
#include "BattleController.h"
#include "Boom.h"
#include "Grow.h"
#include "Camera.h"

AMine::AMine()
{
	name = Mine;
	type = Disposable;
	price = 25;

	temp.Load("mine", 8, 1, 8);
	temp.SetInterval(0.12f);


	renderer->Load("mine_1");
	renderer->SetPosition(Vector(2,20));
	renderer->SetFetchAni(false);

	ani->Insert("idle", temp);
	ani->SetNode("idle");


	ReadyTimeHandle.Bind(20.f, &AMine::Ready,this,false);
}

void AMine::Update()
{
	APlant::Update();

	if (!enabled)return;

	ReadyTimeHandle.Tick();

	if (readyFlag)
	{
		vector<Object*>buf = box->GetCollisions("Zombie");

		if (!buf.empty()) {
			for (auto it = buf.begin(); it != buf.end(); it++) {
				if (AZombie* pZombie = Cast<AZombie>(*it))pZombie->GetAttack(100);
			}
			plants[column][row] = nullptr;
			Destroy();
			MainCamera->Shake(3);
			AudioSource bgm("res/sounds/bulletAttack/mineboom.mp3");
			player->Play(bgm);
			GameStatics::CreateObject<ABoom>(GetWorldPosition());
		}
	}
}

void AMine::Ready()
{
	blood = 1000;
	readyFlag = true;
	renderer->SetFetchAni(true);
	AudioSource bgm("res/sounds/bulletProduce/grow.mp3");
	player->Play(bgm);
	GameStatics::CreateObject<AGrow>(GetWorldPosition());
}
