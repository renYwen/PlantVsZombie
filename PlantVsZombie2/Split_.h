#pragma once
#include"Renderer.h"
#include"Animation.h"
#include"GameStatics.h"

class ASplit_ :public StaticMesh
{
	Animator* ani;
	Animation buf;
	bool flag = false;
public:
	ASplit_()
	{
		ani = GameStatics::ConstructComponent<Animator>(Vector(0, 0));
		ani->SetAttachment(root);
		buf.Load("split_", 6, 1, 6);
		buf.SetInterval(0.06f);
		ani->Insert("idle", buf);
		ani->SetNode("idle");
		renderer->SetLayer(8);
	}
};
