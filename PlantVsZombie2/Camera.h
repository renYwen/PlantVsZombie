#pragma once
#include"CoreMinimal.h"



//Па»ъ
class Camera :public Component
{
	float shakeScale = 0;
	bool shakeFlag = false;
	Vector shakeCenter = Vector(0, 0);
	Vector shakeSpeed = Vector(0.05f, 0.05f);

	int Recorder = 0;
	int Time = 0;
	bool moveFlag = false;
	Vector moveSpeed = Vector(0, 0);
public:
	virtual void Update();
	virtual ~Camera() { ; }

	void SetMain() { MainCamera = this; }

	void Shake(int scale)
	{
		shakeScale = float(scale);
		if (!shakeFlag)shakeCenter = GetLocalPosition();
		shakeFlag = true;
	}

	void MoveTo(Vector aim, float time)
	{
		if (!moveFlag) {
			Vector delta = aim - GetWorldPosition();
			moveSpeed.x = delta.x / (time / DELTA_TIME);
			moveSpeed.y = delta.y / (time / DELTA_TIME);

			Recorder = int(time / DELTA_TIME);
			moveFlag = true;
		}
	}
};