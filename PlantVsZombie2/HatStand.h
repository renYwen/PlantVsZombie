#pragma once
#include"Renderer.h"
#include"Animation.h"
#include"Timer.h"
#include"GameStatics.h"

class AHatStand :public StaticMesh
{
	Animator* ani;
	Animation buf;
	Timer<AHatStand>DestroyTimeHandle;
	bool flag = false;
public:
	AHatStand()
	{
		ani = GameStatics::ConstructComponent<Animator>(Vector(0, 0));
		ani->SetAttachment(root);
		buf.Load("hatstand", 8, 1, 8);
		buf.SetInterval(0.06f);
		ani->Insert("idle", buf);
		ani->SetNode("idle");
		ani->GetNode()->SetIndex(RandEx(0,7));
		DestroyTimeHandle.Bind(10.f, &AHatStand::Destroy, this);
	}
	void Update()
	{
		DestroyTimeHandle.Tick();
	}
};