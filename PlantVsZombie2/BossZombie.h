#pragma once
#include"BaseZombie.h"
#include"Timer.h"

class ABossZombie :public AZombie
{
	Animation attack;
	Animation idle;

	Timer<ABossZombie>BehaviorTimeHandle;
public:
	ABossZombie();
	void Update();
	void Behave();
	int GetBlood() { return blood; }
};