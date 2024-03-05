#pragma once
#include"Renderer.h"
#include"Animation.h"
#include"GameStatics.h"

class AZombieHand :public StaticMesh
{
	Animator* ani;
	Animation buf;
	bool flag = false;
public:
	AZombieHand()
	{
		ani = GameStatics::ConstructComponent<Animator>(Vector(0, 0));
		ani->SetAttachment(root);
		buf.Load("zombieHand", 1, 7, 7);
		buf.SetInterval(0.07f);
		ani->Insert("idle", buf);
		ani->SetNode("idle");
		renderer->SetLayer(5);
	}

	virtual void Update() {
		if (ani->GetNode()->GetAni().index == 6)ani->SetCalled(false);
	}
};