#pragma once
#include"BasePlant.h"
#include"Animation.h"
#include"Timer.h"

class AMine :public APlant
{
	Animation temp;
	bool readyFlag = false;
	Timer<AMine>ReadyTimeHandle;
public:
	AMine();
	void Update();

	void Ready();
};