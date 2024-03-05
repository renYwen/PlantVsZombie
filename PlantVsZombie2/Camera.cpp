#include"Camera.h"
#include"GameStatics.h"


void Camera::Update()
{
	if (moveFlag) {
		AddPosition(moveSpeed);
		Time++;
		if (Time >= Recorder) { Time = 0, moveFlag = false; }
	}

	else if (shakeFlag)
	{
		if (GetLocalPosition() == shakeCenter)
		{
			shakeSpeed.x = float(RandEx(-1, 1));
			shakeSpeed.y = float(RandEx(-1, 1));
			shakeScale -= 0.2f;

			if (shakeScale <= 0) { shakeFlag = false;  return; }
		}

		if (Vector::Dis(shakeCenter, GetLocalPosition()) < shakeScale) {
			AddPosition(shakeSpeed);
		}
		else {
			shakeSpeed.x = -shakeSpeed.x;
			shakeSpeed.y = -shakeSpeed.y;
			AddPosition(Vector(shakeSpeed.x, shakeSpeed.y));
		}
	}
}

extern class Camera* MainCamera{};
