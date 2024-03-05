#pragma once
#include"CoreMinimal.h"
#include"Timer.h"
#include"Resources.h"



//����Դ
class Animation
{
	int num = 1;//������Ŀ
	SpriteInfo ani;//����״̬������ֻ����

	IMAGE* anis = nullptr;//�ڶ��ֶ�����Դ
	
	Timer<Animation>clock;//��ʱ����ֻд��
	
	void Add() { ani.index++; if (ani.index >= num)ani.index = 0; }
public:
	Animation() { ani.flag = 1; clock.Bind(0.f, &Animation::Add, this, true); }
	~Animation() { if (anis)delete []anis; }

	void Update() { clock.Tick(); }

	void Load(string name, int r, int c, int n, Vector delta = Vector(0, 0))//��̬����
	{
		ani.image = ResourcePool.Fetch(name);
		ani.column = c, ani.row = r, num = n, ani.delta = delta;
	}


	void Load_(string path, int wid, int hei, int n, Vector delta = Vector(0, 0))//��̬������֡����
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




//����������
class Animator :public Component
{
	map<string, Animation&>animations;//�洢���ж�����Դ
	Animation* aniNode = nullptr;//��ǰ������Դ
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
