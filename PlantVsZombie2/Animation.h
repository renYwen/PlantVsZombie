#pragma once
#include"CoreMinimal.h"
#include"Timer.h"
#include"Resources.h"



//动画源
class Animation
{
	int num = 1;//动画数目
	SpriteInfo ani;//动画状态参数（只读）

	IMAGE* anis = nullptr;//第二种动画资源
	
	Timer<Animation>clock;//计时器（只写）
	
	void Add() { ani.index++; if (ani.index >= num)ani.index = 0; }
public:
	Animation() { ani.flag = 1; clock.Bind(0.f, &Animation::Add, this, true); }
	~Animation() { if (anis)delete []anis; }

	void Update() { clock.Tick(); }

	void Load(string name, int r, int c, int n, Vector delta = Vector(0, 0))//静态加载
	{
		ani.image = ResourcePool.Fetch(name);
		ani.column = c, ani.row = r, num = n, ani.delta = delta;
	}


	void Load_(string path, int wid, int hei, int n, Vector delta = Vector(0, 0))//动态加载逐帧动画
	{
		anis = new IMAGE[n];
		ani.flag = 2, num = n, ani.delta = delta;
		for (int i = 0; i < n; i++) {
			string temp = path + to_string(i) + string(".png");
			loadimage(&anis[i], temp.c_str(), wid, hei);
		}
	}


	void SetInterval(float time) { clock.SetDelay(time); }
	
	void SetIndex(int i) { ani.index = i; }

	const SpriteInfo& GetAni() { 
		if(ani.flag == 2)ani.image = &(anis[ani.index]);
		return ani;
	}

	int GetNum() { return num; }
};




//动画控制器
class Animator :public Component
{
	map<string, Animation&>animations;//存储所有动画资源
	Animation* aniNode = nullptr;//当前动画资源
	bool isCalled = true;
public:
	Animator() { ; }
	~Animator() { ; }

	virtual void Update() {
		if (aniNode) {
			GetOwner()->SetAniSource((aniNode->GetAni()));
			if (isCalled)aniNode->Update();
		}
	}

	void Insert(string name, Animation& ani)
	{
		animations.insert(pair<string, Animation&>(name, ani));
	}

	Animation* GetNode() { return aniNode; }

	void SetNode(string nodeName)
	{
		aniNode = &(*animations.find(nodeName)).second;
	}

	void SetCalled(bool call) { isCalled = call; }
};
