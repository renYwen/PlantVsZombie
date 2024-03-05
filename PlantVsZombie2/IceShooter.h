#pragma once
#include"BasePlant.h"
#include"Animation.h"

class AIceShooter :public APlant
{
	Animation temp;
	bool attackFlag = false;
public:
	AIceShooter();
	void Update();

	void Shoot();
};