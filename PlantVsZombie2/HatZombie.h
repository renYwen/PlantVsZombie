#pragma once
#include"BaseZombie.h"


class AHatZombie :public AZombie
{
	Animation walk;
	Animation eat;
	Animation die;
	Animation walk_1;
	Animation eat_1;
	Animation die_1;

	bool pattern = true;
public:
	AHatZombie();
	void Update() { 
		AZombie::Update(); 
		if (blood <= 10 && pattern) {
			walk.SetInterval(0.06f);
			eat.SetInterval(0.03f);
			walk_1.SetInterval(0.12f);
			eat_1.SetInterval(0.06f);
			walk.Load("normalwalk", 5, 10, 46);
			eat.Load("normaleat", 4, 10, 39, Vector(-3, 0));
			walk_1.Load("normalwalk_1", 5, 10, 46);
			eat_1.Load("normaleat_1", 4, 10, 39, Vector(-3, 0));
			pattern = false;
		}
	}
};