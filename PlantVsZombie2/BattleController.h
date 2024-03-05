#pragma once
#include "Controller.h"
#include "Timer.h"



extern class APlant* plants[9][5];//草坪植物信息
extern int zombieNumPerRow[5];//每行僵尸数量


class ABattleController :public Controller
{
	bool bAniFlag = true;//开场动画
	Timer<ABattleController>AnimationTimeHandle;

	class UBattleUI* ui;
	class APlant* plant = nullptr;
	class APlant* prePlant = nullptr;
	class APlant** plantUnderScoop = nullptr;
	int curIndex = -1;
	

	bool comeFlag = true;
	int zombieNum = 0;
	int rollPattern = 0;//草坪模式

	class AudioPlayer* player;
	Timer<ABattleController>SunTimeHandle;
	Timer<ABattleController>MainControlTimeHandle;
	Timer<ABattleController>BlinkTimeHandle;
	Timer<ABattleController>BossGenerateTimeHandle;

	class ABossZombie* boss=nullptr;//boss
public:
	int sunShine = 50;
	//int sunShine = 10000;/* for Debug */

	ABattleController();

	void Update();

	static Pair FindCoordinate(Vector pos)
	{
		int x = pos.x - 30, y = pos.y - 90;
		if (x < 0 || y < 0)return Pair(-1, -1);
		return Pair(x/80, y/100);
	}

	void Produce();//产阳光

	void Generate();//产僵尸
	void Generate_();//产僵尸(boss)

};