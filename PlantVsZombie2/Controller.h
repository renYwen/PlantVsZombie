#pragma once
#include "BoxCollider.h"


//玩家控制器类
class Controller :public Object
{
protected:
	ExMessage msg;
public:

	virtual void Update() { if (logPattern && msg.lbutton)cout<<GetCursorScreenPosition()<<" "; }

	void PeekInfo() { peekmessage(&msg); }
	
	const ExMessage& GetCursorMessage() { return msg; }

	Vector GetCursorWorldPosition();
	
	Vector GetCursorScreenPosition() { return Vector(msg.x, msg.y); }

	void SetPossession(){MainController = this;}

	bool BoxJudgeUnderCursor(BoxCollider* another);

	vector<Object*>GetObjectsUnderCursor();//所获得的对象必须有碰撞箱

	template<class T>
	T* GetObjectUnderCursor();//所获得的对象必须有碰撞箱

};

template<class T>
T* Controller::GetObjectUnderCursor()
{
	for (auto it = GameColliders.begin(); it != GameColliders.end(); ++it)
	{
		if (BoxJudgeUnderCursor(*it))
			if (T* aim = Cast<T>((*it)->GetOwner()))return aim;
	}
}