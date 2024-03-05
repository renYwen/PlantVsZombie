#include "DoubleShooter.h"
#include "GameStatics.h"
#include "Pea.h"
#include "Audio.h"
#include "BattleController.h"

ADoubleShooter::ADoubleShooter()
{
	name = DoubleShooter;
	type = Shooter;
	price = 200;

	temp.Load("doubleshooter", 4, 6, 24);
	temp.SetInterval(0.06f);

	shade->AddPosition(Vector(0, -5));

	ani->Insert("idle", temp);
	ani->SetNode("idle");

}

void ADoubleShooter::Update()
{
	APlant::Update();

	if (ani->GetNode()->GetAni().index == 0)
		attackFlag = 1;
	if (ani->GetNode()->GetAni().index == 10 
		&& zombieNumPerRow[row] > 0 && attackFlag == 1) {
		Shoot(); attackFlag = 2;
	}
	if (ani->GetNode()->GetAni().index == 13 && attackFlag == 2) {
		Shoot(); attackFlag = 0;
	}
}

void ADoubleShooter::Shoot()
{
	GameStatics::CreateObject<APea>(Vector(GetWorldPosition().x + 50, GetWorldPosition().y + 10));
	AudioSource bgm;
	bgm.Load("res/sounds/bulletProduce/doubleshoot.mp3");
	player->Play(bgm);
}
