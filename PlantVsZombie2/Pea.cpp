#include "Pea.h"
#include"Animation.h"
#include"BoxCollider.h"
#include"BaseZombie.h"
#include"GameStatics.h"
#include "PeaPieces.h"

APea::APea()
{
	damage = 1;
	speed = Vector(3.f,0);

	renderer->Load("pea");
	renderer->SetLayer(8);

	shade = GameStatics::ConstructComponent<SpriteRenderer>(Vector(0, 50));
	shade->SetAttachment(root);
	shade->Load("smallShadow");
	shade->SetFetchAni(false);
	shade->SetTransparency(200);


	box->SetSize(Vector(25, 25));
	box->SetColor(LIGHTBLUE);

}

void APea::Update()
{
	AddPosition(speed);

	if (GetWorldPosition().x > 825)Destroy();

	vector<Object*>buf = box->GetCollisions("Zombie");
	
	if (!buf.empty()) {
		if (AZombie* pZombie = Cast<AZombie>(buf[0])) {
			pZombie->GetAttack(damage);
			this->Destroy();
			GameStatics::CreateObject<APeaPieces>(GetWorldPosition());
		}
	}
}
