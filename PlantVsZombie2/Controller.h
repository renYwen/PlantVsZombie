#pragma once
#include "BoxCollider.h"


//��ҿ�������
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

	vector<Object*>GetObjectsUnderCursor();//����õĶ����������ײ��

	template<class T>
	T* GetObjectUnderCursor();//����õĶ����������ײ��

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