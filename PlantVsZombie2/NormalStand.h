#pragma once
#include"Renderer.h"
#include"Animation.h"
#include"Timer.h"
#include"GameStatics.h"

class ANormalStand:public StaticMesh
{
	Animator* ani;
	Animation buf;
	Timer<ANormalStand>DestroyTimeHandle;
	bool flag = false;
public:
	ANormalStand()
	{
		ani = GameStatics::ConstructComponent<Animator>(Vector(0, 0));
		ani->SetAttachment(root);
		buf.Load("normalstand", 11, 1, 11);
		buf.SetInterval(0.06f);
		ani->Insert("idle", buf);
		ani->SetNode("idle");
		ani->GetNode()->SetIndex(RandEx(0, 10));
		DestroyTimeHandle.Bind(10.f, &ANormalStand::Destroy, this);
	}
	void Update()
	{
		DestroyTimeHandle.Tick();
	}
};
