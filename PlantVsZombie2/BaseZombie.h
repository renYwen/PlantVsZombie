#pragma once
#include"Renderer.h"
#include"Timer.h"
#include"Animation.h"

class AZombie :public StaticMesh
{
protected:
	ZombieName name = NormalZombie;

	class BoxCollider* box;
	vector<class APlant*>collisons;
	Animator* ani;
	Animation ash;
	bool bAsh = false;

	class AudioPlayer* player;
	Timer<AZombie>EatTimeHandle;
	Timer<AZombie>BlinkTimeHandle;
	Timer<AZombie>RecoverTimeHandle;//减速恢复计时器

	int state = 0;//状态（0走路，1吃植物，2死亡）
	Vector speed = Vector(-0.06f, 0);
	int blood = 10;

	SpriteRenderer* shade;
	float slowFlag = 2;//减速标记（2正常，1减速）
public:
	int row = 0;

	AZombie();

	virtual void Update();

	virtual void Judge();

	void Eat();

	void GetAttack(int harm,bool boom=false);

	void Recover();

	void Freeze();

	ZombieName GetName() { return name; }
};


