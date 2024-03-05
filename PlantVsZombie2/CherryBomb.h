#pragma once
#include"BasePlant.h"
#include"Animation.h"


class ACherryBomb :public APlant
{
	Animation temp;
public:
	ACherryBomb();
	void Update();
};