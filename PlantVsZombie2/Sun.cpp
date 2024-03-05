#include "Sun.h"
#include "GameStatics.h"
#include "BoxCollider.h"
#include "BattleController.h"
#include "Audio.h"
#include "RigidBody.h"

ASun::ASun()
{
	renderer->SetLayer(10);
	
	temp.Load("sun", 2, 6, 12);
	temp.SetInterval(0.12f);

	rigid = GameStatics::ConstructComponent<RigidBody>(Vector(0,0));
	rigid->SetAttachment(root);

	ani = GameStatics::ConstructComponent<Animator>(Vector(0, 0));
	ani->SetAttachment(root);
	ani->Insert("idle", temp);
	ani->SetNode("idle");

	player = GameStatics::ConstructComponent<AudioPlayer>(Vector(0, 0));
	player->SetAttachment(root);

	box->SetSize(Vector(75, 75));
	box->SetColor(YELLOW);


	MissTimeHandle.Bind(9.3f, &ASun::SetMissing, this, false);
	DestroyTimeHandle.Bind(10.f, &ASun::Destroy, this, false);
}

void ASun::Update()
{
	if (ABattleController* buf = Cast<ABattleController>(MainController)) {

		if (!isClicked) {
			DestroyTimeHandle.Tick();
			MissTimeHandle.Tick();

			if (missing)
			{
				renderer->SetTransparency(renderer->GetTransparency() - 3);
			}

			if (box->IsUnderCursor() && buf->GetCursorMessage().lbutton) {
				isClicked = true;

				AudioSource bgm("res/sounds/bulletAttack/sunclick.mp3");
				player->Play(bgm);

				Vector pos = GetWorldPosition();
				rigid->SetMovable(true);
				rigid->SetVelocity(Vector(-pos.x * DELTA_TIME * 2, -pos.y * DELTA_TIME * 2));
				rigid->EnableGravity(false);
				
			}
			else if (GetWorldPosition().y >= line) rigid->SetMovable(false);
		}
		else
		{
			if (GetWorldPosition().y < 0)
			{
				buf->sunShine += 25;
				this->Destroy();
			}
		}
	}
	
}




