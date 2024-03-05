#pragma once
#include"BasePlant.h"
#include"Animation.h"

class APeaShooter:public APlant
{
	Animation temp;
	bool attackFlag = false;
public:
	APeaShooter();
	void Update();

	void Shoot();
};