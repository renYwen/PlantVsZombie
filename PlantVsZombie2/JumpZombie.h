#pragma once
#include"BaseZombie.h"


class AJumpZombie :public AZombie
{
	Animation walk;
	Animation run;
	Animation jump;
	Animation eat;
	Animation die;

	Animation walk_1;
	Animation run_1;
	Animation jump_1;
	Animation eat_1;
	Animation die_1;

public:
	AJumpZombie();
	void Update();
	void Judge();
};
