#include"BasePlant.h"
#include"GameStatics.h"
#include"BoxCollider.h"
#include"Animation.h"
#include"Audio.h"
#include "BattleController.h"

APlant::APlant()
{
	ani = GameStatics::ConstructComponent<Animator>(Vector(0, 0));
	ani->SetAttachment(root);
	ani->SetCalled(enabled);

	shade = GameStatics::ConstructComponent<SpriteRenderer>(Vector(7, 50));
	shade->SetAttachment(root);
	shade->Load("bigShadow");
	shade->SetFetchAni(false);
	shade->SetTransparency(0);

	box = GameStatics::ConstructComponent<BoxCollider>(Vector(15,10));
	box->SetAttachment(root);
	box->SetType("Plant");
	box->SetSize(Vector(50,60));

	player = GameStatics::ConstructComponent<AudioPlayer>(Vector(0, 0));
	player->SetAttachment(root);
}

void APlant::Update()
{
	if(flag && enabled){
		renderer->SetLayer(row+1);
		shade->SetTransparency(225);
		ani->SetCalled(enabled);
		flag = false;
	}


	if (blood <= 0) {
		AudioSource bgm;
		bgm.Load("res/sounds/zombieEat/eat_finish.mp3");
		player->Play(bgm);
		plants[column][row] = nullptr;
		Destroy();
	}

	if (enabled && BlinkTimeHandle.GetDelay() > 0.25 && renderer->GetTransparency()>=200)
		renderer->SetTransparency(255);
}
