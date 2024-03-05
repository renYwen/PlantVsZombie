#pragma once
#include"Renderer.h"
#include"Timer.h"

class ABomb :public StaticMesh
{
	Timer<ABomb>DestroyTimeHandle;
public:
	ABomb()
	{
		DestroyTimeHandle.Bind(0.5f, &ABomb::Destroy, this, false);
		renderer->Load("explosion");
		renderer->SetLayer(10);
	}

	virtual void Update() { DestroyTimeHandle.Tick(); }
};