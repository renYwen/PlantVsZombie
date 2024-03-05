#pragma once
#include"BasePlant.h"
#include"Animation.h"

class ADoubleShooter :public APlant
{
	Animation temp;
	int attackFlag = 0;
public:
	ADoubleShooter();
	void Update();

	void Shoot();
};