#pragma once
#include"BaseZombie.h"


class ANormalZombie :public AZombie
{
	Animation walk;
	Animation eat;
	Animation die;
	Animation walk_1;
	Animation eat_1;
	Animation die_1;
public:
	ANormalZombie();
	void Update() { AZombie::Update(); }
};
