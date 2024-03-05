#pragma once
#include"Renderer.h"
#include"Animation.h"
#include"GameStatics.h"

class AGrow :public StaticMesh
{
	Animator *ani;
	Animation buf;
	bool flag = false;
public:
	AGrow()
	{
		ani = GameStatics::ConstructComponent<Animator>(Vector(0, 0));
		ani->SetAttachment(root);
		buf.Load("soil",4, 1, 4);
		buf.SetInterval(0.08f);
		ani->Insert("idle",buf);
		ani->SetNode("idle");
		renderer->SetLayer(8);
	}

	virtual void Update(){
		if (ani->GetNode()->GetAni().index == 3 && !flag)flag = true;
		
		if (ani->GetNode()->GetAni().index == 0 && flag)Destroy();
	}
};