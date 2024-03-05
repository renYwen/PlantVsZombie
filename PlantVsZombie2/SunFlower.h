#pragma once
#include"BasePlant.h"
#include "Timer.h"
#include"Animation.h"

class ASunFlower :public APlant
{
	Animation temp;
	Animation temp_1;
	Timer<ASunFlower>ProduceTimeHandle;
	Timer<ASunFlower>* PreTimeHandle = nullptr;
public:
	ASunFlower();
	~ASunFlower() { if (PreTimeHandle) delete PreTimeHandle; }
	void Update();


	void Produce();
	void Pre();
};