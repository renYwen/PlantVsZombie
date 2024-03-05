#pragma once
#include"Renderer.h"
#include"Animation.h"
#include"GameStatics.h"

class ASplit :public StaticMesh
{
	Animator* ani;
	Animation buf;
	bool flag = false;
public:
	ASplit()
	{
		ani = GameStatics::ConstructComponent<Animator>(Vector(0, 0));
		ani->SetAttachment(root);
		buf.Load("split", 6, 1, 6);
		buf.SetInterval(0.06f);
		ani->Insert("idle", buf);
		ani->SetNode("idle");
		renderer->SetLayer(8);
	}
};
