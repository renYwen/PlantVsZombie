#pragma once
#include"BasePlant.h"
#include"Animation.h"
#include"Timer.h"

class AChomper :public APlant
{
	Animation temp;
	Animation temp_1;
	Animation temp_2;
	int state = 0;
	Timer<AChomper>ChompTimeHandle;
	class BoxCollider* eatBox;
	bool eatFlag = false;
public:
	AChomper();
	void Update();
	void EatUp();
};