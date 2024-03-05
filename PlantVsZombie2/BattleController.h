#pragma once
#include "Controller.h"
#include "Timer.h"



extern class APlant* plants[9][5];//��ƺֲ����Ϣ
extern int zombieNumPerRow[5];//ÿ�н�ʬ����


class ABattleController :public Controller
{
	bool bAniFlag = true;//��������
	Timer<ABattleController>AnimationTimeHandle;

	class UBattleUI* ui;
	class APlant* plant = nullptr;
	class APlant* prePlant = nullptr;
	class APlant** plantUnderScoop = nullptr;
	int curIndex = -1;
	

	bool comeFlag = true;
	int zombieNum = 0;
	int rollPattern = 0;//��ƺģʽ

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

	void Produce();//������

	void Generate();//����ʬ
	void Generate_();//����ʬ(boss)

};