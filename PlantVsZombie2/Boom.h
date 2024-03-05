#pragma once
#include"Renderer.h"
#include"Timer.h"

class ABoom :public StaticMesh
{
	Timer<ABoom>DestroyTimeHandle;
public:
	ABoom()
	{
		DestroyTimeHandle.Bind(0.5f, &ABoom::Destroy, this, false);
		renderer->Load("boom");
		renderer->SetLayer(10);
	}

	virtual void Update() { DestroyTimeHandle.Tick(); }
};