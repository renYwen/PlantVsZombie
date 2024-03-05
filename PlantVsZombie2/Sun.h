#pragma once
#include"BaseBullet.h"
#include"Animation.h"

class ASun :public ABullet
{
	class AudioPlayer* player;
	class Animator* ani;
	Animation temp;
	bool isClicked = false;

	bool missing = false;
	Timer<ASun>MissTimeHandle;
	Timer<ASun>DestroyTimeHandle;
public:
	int line = 0;
	class RigidBody* rigid;
	ASun();
	void Update();
	void SetMissing() { missing = true; }
};