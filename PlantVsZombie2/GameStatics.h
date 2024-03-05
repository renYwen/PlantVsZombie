
/* API */

#pragma once
#include "CoreMinimal.h"
#include "Camera.h"


class GameStatics
{
public:

	//创建游戏对象
	template<class T>
	static T* CreateObject(Vector pos);

	//获取所有对象实例
	template<class T>
	static set<T*> GetAllObjects();

	//清理所有对象实例
	static void DeleteObjects()
	{
		for (auto it = GameObjects.begin(); it != GameObjects.end(); ++it)
		{
			delete (*it);
		}
		GameObjects.clear();
	}

	//创建组件对象
	template<class T>
	static T* ConstructComponent(Vector pos);


	//创建UI对象
	template<class T>
	static T* CreateUI();


	//获取玩家控制器实例
	static Controller* GetController()
	{
		return MainController;
	}

	//加载新的场景
	template<class T>
	static void OpenLevel();

};


template<class T>
inline T* GameStatics::CreateObject(Vector pos)
{
	T* gameObj = new T;
	if (Object* buf = static_cast<Object*>(gameObj)) {
		buf->SetPosition(pos);
		GameObjects.insert(buf);
	}
	else
	{
		delete gameObj;
		gameObj = nullptr;
		cout << "Fail To Create" << endl;
	}
	return gameObj;
}

template<class T>
inline set<T*>GameStatics::GetAllObjects()
{
	set<T*>DesSet;
	set<Object*>::iterator it;
	for (it = GameObjects.begin(); it != GameObjects.end(); ++it)
	{
		if (T* des = dynamic_cast<T*>(*it))
			DesSet.insert(des);
	}
	return DesSet;
}

template<class T>
inline T* GameStatics::ConstructComponent(Vector pos)
{
	T* gameCom = new T;
	if (Component* buf = static_cast<Component*>(gameCom)) {
		buf->SetPosition(pos);
		GameComponents.insert(buf);
	}
	else
	{
		delete gameCom;
		gameCom = nullptr;
		cout << "Fail To Create" << endl;
	}
	return gameCom;
}

template<class T>
inline T* GameStatics::CreateUI()
{
	T* gameUI = new T;
	if (UserInterface* buf = static_cast<UserInterface*>(gameUI)) {
		GameUIs.insert(buf);
	}
	else
	{
		delete gameUI;
		gameUI = nullptr;
		cout << "Fail To Create" << endl;
	}
	return gameUI;
}

template<class T>
inline void GameStatics::OpenLevel()
{
	for (auto it = GameObjects.begin(); it != GameObjects.end(); ++it)
	{
		delete (*it);
	}
	GameObjects.clear();
	for (auto it = GameComponents.begin(); it != GameComponents.end(); ++it)
	{
		delete (*it);
	}
	GameComponents.clear();
	for (auto it = GameUIs.begin(); it != GameUIs.end(); ++it)
	{
		delete (*it);
	}
	GameUIs.clear();

	GameObjects_.clear();
	GameComponents_.clear();
	GameUIs_.clear();

	GameRenders.clear();
	GamePainters.clear();
	GameColliders.clear();
	
	changeLevel = true;

	MainCamera = GameStatics::ConstructComponent<Camera>(Vector(0, 0));
	MainController = GameStatics::CreateObject<T>(Vector(0, 0));
}
