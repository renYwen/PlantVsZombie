#pragma once
#include "Controller.h"
#include "Timer.h"


class AMenuController :public Controller
{
	class UMenuUI* ui;
	class AudioPlayer* player;
	Timer<AMenuController>RiskTimeHandle;
	class AZombieHand* hand = nullptr;
public:
	AMenuController();

	void Update();
};