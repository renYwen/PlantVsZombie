#pragma once
#include"BaseBullet.h"

class AIcePea :public ABullet
{
	SpriteRenderer* shade;
public:
	AIcePea();
	void Update();
};