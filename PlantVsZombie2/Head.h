#pragma once
#include"Renderer.h"
#include"Animation.h"
#include"GameStatics.h"
#include"Timer.h"

class AHead :public StaticMesh
{
	Animator* ani;
	Animation temp;
	Animation temp_1;
	Timer<AHead>DestroyTimeHandle;
public:
	AHead()
	{
		ani = GameStatics::ConstructComponent<Animator>(Vector(0, 0));
		ani->SetAttachment(root);

		temp.Load("head", 12, 1, 12);
		temp.SetInterval(0.08f);
		temp_1.Load("head_1", 12, 1, 12);
		temp_1.SetInterval(0.08f);

		ani->Insert("idle", temp);
		ani->Insert("idle_1", temp_1);
		ani->SetNode("idle");

		DestroyTimeHandle.Bind(1.75f,&AHead::Destroy,this,false);
	}

	virtual void Update() {
		if (ani->GetNode()->GetAni().index == 11)ani->SetCalled(false);
		DestroyTimeHandle.Tick();
	}

	void Func()
	{
		ani->SetNode("idle_1");
	}

};