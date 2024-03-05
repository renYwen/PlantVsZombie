#pragma once
#include"Renderer.h"


class ABullet :public StaticMesh
{
protected:
	int damage = 0;
	Vector speed = Vector(0,0);

	class BoxCollider* box;
public:
	int row = 0;

	ABullet();

	virtual void Update() { ; }

	void SetSpeed(Vector sp) { speed = sp; }
};