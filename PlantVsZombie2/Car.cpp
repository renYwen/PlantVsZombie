#include "Car.h"
#include"GameStatics.h"
#include"BoxCollider.h"
#include"Audio.h"
#include"BaseZombie.h"

ACar::ACar()
{
	box = GameStatics::ConstructComponent<BoxCollider>(Vector(0, 0));
	box->SetAttachment(root);
	box->SetType("Car");
	box->SetSize(Vector(60, 45));

	player = GameStatics::ConstructComponent<AudioPlayer>(Vector(0, 0));
	player->SetAttachment(root);

	renderer->Load("car");
}

void ACar::Update()
{
	if (enable) { 
		AddPosition(speed); 
		if (speed.x < 5)speed +=Vector(0.05,0);
	}

	if (GetWorldPosition().x == -25)enable = false;

	if (GetWorldPosition().x > 1000)Destroy();

	vector<Object*>buf = box->GetCollisions("Zombie");

	if (!buf.empty()) {
		if (!enable)
		{
			enable = true; AddPosition(speed);
			AudioSource bgm;
			bgm.Load("res/sounds/car.mp3");
			player->Play(bgm);
		}
		speed = Vector(2, 0);

		AudioSource bgm;
		bgm.Load("res/sounds/bulletAttack/carcrash.mp3");
		player->Play(bgm);
		for (int i = 0; i < buf.size(); i++)
		{
			if (AZombie* pZombie = Cast<AZombie>(buf[i])) { 
				if(pZombie->GetName()!=BossZombie)pZombie->GetAttack(300); 
				else pZombie->GetAttack(10);
			}
		}
	}
}



