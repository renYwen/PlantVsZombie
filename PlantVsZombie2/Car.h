#pragma once
#include"Renderer.h"


class ACar :public StaticMesh
{
protected:
	Vector speed = Vector(5, 0);
	bool enable = true;

	class AudioPlayer* player;

	class BoxCollider* box;
public:
	int row = 0;

	ACar();

	virtual void Update();
};