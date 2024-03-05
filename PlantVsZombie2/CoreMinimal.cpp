#include "CoreMinimal.h"


extern set<Object*>GameObjects{};

extern set<Component*>GameComponents{};

extern vector<Object*>GameObjects_{};

extern vector<Component*>GameComponents_{};

extern set<DWORD*>GameLastTimes{};

extern DWORD pauseTime = 0;
extern IMAGE pauseImage{};
extern bool pause = false;

extern bool logPattern = false;

extern bool changeLevel = false;

extern int RandEx(int up, int down)
{
	LARGE_INTEGER seed;
	QueryPerformanceFrequency(&seed);
	QueryPerformanceCounter(&seed);
	srand(unsigned(seed.QuadPart));
	int scoop = down - up+1;
	scoop = scoop > 0 ? scoop : -scoop;
	return rand() % scoop + up;
}

Vector Component::GetWorldPosition()
{
	if (parent)
		return parent->GetWorldPosition() + GetLocalPosition();
	else
	{
		if(owner)return owner->GetWorldPosition();
		else return GetLocalPosition();
	}
}

float Component::GetWorldRotation()
{
	if (parent)
		return parent->GetWorldRotation() + GetLocalRotation();
	else
	{
		if (owner)return owner->GetWorldRotation();
		else return GetLocalRotation();
	}
}


