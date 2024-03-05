#pragma once
#include"BasePlant.h"
#include"Animation.h"

class AWallNut :public APlant
{
	Animation temp;
	Animation temp_1;
	Animation temp_2;
	int crackFlag = 0;
public:
	AWallNut();
	void Update();
};