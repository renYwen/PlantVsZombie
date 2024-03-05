#pragma once
#include"CoreMinimal.h"


//¸ÕÌå£¨ÎïÀí£©
class RigidBody :public Component
{
	Vector velocity = Vector(0,0);
	bool gravityEnabled = true;
	float gravity = 10.f;
	bool movable = true;
public:
	
	virtual void Update()
	{
		if (movable)
		{
			if(gravityEnabled)
			velocity.y += gravity * DELTA_TIME;

			if(Object* owner = GetOwner())
			owner->AddPosition(velocity);
		}
	}

	void EnableGravity(bool en) { gravityEnabled = en; }
	
	void SetGravity(float gra) { gravity = gra; }

	void SetMovable(bool mov) { movable = mov; }

	void SetVelocity(Vector vel) { velocity = vel; }
};