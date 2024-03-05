#pragma once
#include"Renderer.h"
#include"Timer.h"

class AIcePieces :public StaticMesh
{
	Timer<AIcePieces>DestroyTimeHandle;
	int num = 0;
public:
	AIcePieces()
	{
		DestroyTimeHandle.Bind(0.2f, &AIcePieces::Destroy, this, false);
		renderer->Load("icepea_1");
		renderer->SetLayer(8);
	}

	virtual void Update() { DestroyTimeHandle.Tick(); renderer->SetTransparency(num -= 10); }
};
