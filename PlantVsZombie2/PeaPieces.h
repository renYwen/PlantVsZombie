
#pragma once
#include"Renderer.h"
#include"Timer.h"

class APeaPieces :public StaticMesh
{
	Timer<APeaPieces>DestroyTimeHandle;
	int num = 255;
public:
	APeaPieces()
	{
		DestroyTimeHandle.Bind(0.2f, &APeaPieces::Destroy, this, false);
		renderer->Load("pea_1");
		renderer->SetLayer(8);
	}

	virtual void Update() { DestroyTimeHandle.Tick(); renderer->SetTransparency(num-=10);}
};