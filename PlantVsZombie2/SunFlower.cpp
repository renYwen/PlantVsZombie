#include "SunFlower.h"
#include "GameStatics.h"
#include "Camera.h"
#include "Sun.h"
#include "RigidBody.h"
#include "Audio.h"

ASunFlower::ASunFlower()
{
	name = SunFlower;
	type = Producer;
	price = 50;
	

	temp.Load("sunflower",4, 6, 24);
	temp.SetInterval(0.06f);
	
	temp_1.Load("sunflower_1", 4, 6, 24);
	temp_1.SetInterval(0.06f);

	ani->Insert("idle", temp);
	ani->Insert("produce", temp_1);
	ani->SetNode("idle");

	ProduceTimeHandle.Bind(20.8f, &ASunFlower::Pre, this, true);
}

void ASunFlower::Update()
{
	APlant::Update();
	if (!enabled)return;

	ProduceTimeHandle.Tick();
	if(PreTimeHandle)
	PreTimeHandle->Tick();

}

void ASunFlower::Produce()
{
	ani->SetNode("idle");
	
	ASun* temp = GameStatics::CreateObject<ASun>(Vector(GetWorldPosition().x, GetWorldPosition().y));
	temp->rigid->SetVelocity(Vector(float(RandEx(-10, 10))/10,-2));
	temp->line = GetWorldPosition().y+5;

	AudioSource bgm;
	bgm.Load("res/sounds/bulletProduce/produce.mp3");
	player->Play(bgm);

	delete PreTimeHandle; PreTimeHandle = nullptr;
}

void ASunFlower::Pre()
{
	int index = ani->GetNode()->GetAni().index;
	ani->SetNode("produce");
	ani->GetNode()->SetIndex(index);
	PreTimeHandle = new Timer<ASunFlower>;
	PreTimeHandle->Bind(1.44f, &ASunFlower::Produce, this, false);
}


