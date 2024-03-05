#include "Controller.h"
#include "Camera.h"





Vector Controller::GetCursorWorldPosition()
{
	return Vector(msg.x, msg.y) + MainCamera->GetWorldPosition();
}

bool Controller::BoxJudgeUnderCursor(BoxCollider* another)
{
	float x = MainCamera->GetWorldPosition().x + msg.x,y = MainCamera->GetWorldPosition().y + msg.y;
	float x_a = another->GetWorldPosition().x, y_a = another->GetWorldPosition().y;
	if (x<x_a + another->GetSize().x && x>x_a && y<y_a + another->GetSize().y && y>y_a)
	{
		return true;
	}
	return false;
}


vector<Object*> Controller::GetObjectsUnderCursor()
{
	vector<Object*>aims;
	for (auto it = GameColliders.begin(); it != GameColliders.end(); ++it)
	{
		if (BoxJudgeUnderCursor(*it))aims.push_back((*it)->GetOwner());
	}
	return aims;
}

extern Controller* MainController{};