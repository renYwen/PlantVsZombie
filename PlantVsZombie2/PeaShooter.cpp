#include "PeaShooter.h"
#include "GameStatics.h"
#include "Pea.h"
#include "Audio.h"
#include "BattleController.h"

APeaShooter::APeaShooter()
{
	name = PeaShooter;
	type = Shooter;
	price = 100;
	
	temp.Load("peashooter",4, 6, 24);
	temp.SetInterval(0.06f);

	shade->AddPosition(Vector(0,-5));
	
	ani->Insert("idle",temp);
	ani->SetNode("idle");

}

void APeaShooter::Update()
{
	APlant::Update();

	if (ani->GetNode()->GetAni().index == 0)
		attackFlag = true;
	if (ani->GetNode()->GetAni().index == 11 && attackFlag) {
		Shoot(); attackFlag = false;
	}
}

void APeaShooter::Shoot()
{
	if (zombieNumPerRow[row]>0) {
		GameStatics::CreateObject<APea>(Vector(GetWorldPosition().x + 50, GetWorldPosition().y + 1));
		AudioSource bgm("res/sounds/bulletProduce/shoot.mp3");
		player->Play(bgm);
	}
}

