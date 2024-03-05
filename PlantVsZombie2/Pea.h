#pragma once
#include"BaseBullet.h"

class APea :public ABullet
{
	SpriteRenderer* shade;
public:
	APea();
	void Update();
};