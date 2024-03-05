/******************************************************
 * 核心代码头文件
 * 
 * 基础外部头文件，基础API，基础枚举，基础类，基础结构体，基础变量等
 *     —— By Arty 2024.1.19
 ******************************************************/


#pragma once
/* 外部头文件 */


///图形渲染
#include<easyx.h>//图形库API
#include<winuser.h>
#pragma comment(lib, "MSIMG32.LIB")//背景透明函数

///多媒体
#include<mmsystem.h>//包含多媒体设备接口
#pragma comment(lib,"winmm.lib")//加载静态库


///其他
#include<iostream>//I/O
#include<string>//字符串
#include<algorithm>//算法
#include<math.h>//数学API
#include<fstream>//文件读写

#include "Overall.h"//全局变量

using namespace std;



/* enum */

//植物种类名
enum PlantName
{
	PeaShooter, SunFlower, CherryBomb, Nut, Mine, IceShooter, Chomper, DoubleShooter
};

//僵尸种类
enum ZombieName
{
	NormalZombie, HatZombie, BucketZombie,JumpZombie,ArmorZombie,BossZombie
};

//植物功能种类
enum PlantType
{
	Shooter,Producer,Disposable,Protector,Thrower,Other
};

//碰撞图层种类名
enum CollisonType
{
	Default,Plant,Zombie,Bullet,Cursor
};



/* class and struct */

//二维向量
struct Vector
{
	float x = 0;
	float y = 0;
	Vector() {}
	Vector(float a, float b) :x(a), y(b) {}
	static float Dis(const Vector& a,const Vector& b){
		return sqrtf((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
	}
	Vector operator+(const Vector& another)const{
		return Vector(x + another.x, y + another.y);
	}
	Vector operator-(const Vector& another)const{
		return Vector(x - another.x, y - another.y);
	}
	Vector& operator+=(const Vector& another){
		x += another.x, y += another.y;
		return *this;
	}
	Vector& operator-=(const Vector& another) {
		x -= another.x, y -= another.y;
		return *this;
	}
	bool operator==(const Vector& another)const {
		return (another.x==x) && (another.y == y);
	}

	
	Vector operator*(float another)const {
		return Vector(x * another, y * another);
	}
	Vector& operator*=(float another){
		x *= another, y *= another;
		return *this;
	}

	float operator*(const Vector& another)const //点积
	{
		return x * another.x+ y * another.y;
	}

	friend ostream& operator<<(ostream& out, const Vector& vec);

};

static ostream& operator<<(ostream& out, const Vector& vec)
{
	out << "(" << vec.x << "," << vec.y << ")";
	return out;
}

//二维数对
struct Pair
{
	int x=0;
	int y=0;
	Pair() {}
	Pair(int i, int j) :x(i), y(j) {}
	bool operator==(const Pair& another)const {
		return (another.x == x) && (another.y == y);
	}
	bool operator<(const Pair& another)const {
		if (x == another.x)
			return y < another.y;
		return x<another.x;
	}
};


//基本变换属性成员
struct Transform
{
	Vector position = Vector(0, 0);
	float rotation = 0;
	Transform() {}
	Transform(Vector pos,float rot)
		:position(pos),rotation(rot){}

};

//基础渲染信息
struct SpriteInfo
{
	IMAGE* image = nullptr;

	Vector delta = Vector(0, 0);
	//资源位置偏移(解决同一渲染器渲染不同动画资源位置偏差问题)

	int flag = 0;//动画标记（0表示无动画，1表示整张动画资源，2表示分开动画资源）

	/* 以下信息均为一整张sprite类动画资源独有 */
	int index = 0;
	int row = 1;
	int column = 1;

	const SpriteInfo& operator=(const SpriteInfo& another)
	{
		image = another.image;
		flag = another.flag;
		index = another.index;
		row = another.row;
		column = another.column;
		delta = another.delta;
		return *this;
	}

};



//补充渲染信息
struct SpriteInfo_
{
	bool isUsed = false;
	Vector aimSize = Vector(0,0);
	Vector aimLoc = Vector(0, 0);
};


//场景组件类（基类）
class Component
{
	friend class Object;
	void SetOwner(class Object* own) {
		if (!owner)owner = own; else cout << "please use SetAttachment instead" << endl;
	}
protected:
	class Object* owner = nullptr;
	Transform transform;
	Component* parent = nullptr;
	set<Component*>sons;
	void process_Destruct()
	{
		if (!sons.empty()) {
			for (auto it = sons.begin(); it != sons.end(); ++it) {
				(*it)->process_Destruct();
			}
		}
		GameComponents_.push_back(this);
	}

public:
	Component() { ; }
	virtual ~Component() { ; }

	virtual void Update() { ; }

	class Object* GetOwner() { return owner; }


	Transform GetTransform() { return transform; }

	void SetAttachment(Component* par) {
		if (parent)parent->sons.erase(this);
		parent = par;
		par->sons.insert(this);

		while (par->parent)par = par->parent;
		owner = par->owner;
	}

	void Destruct()
	{
		if (parent)parent->sons.erase(this);

		process_Destruct();
	}

	Vector GetWorldPosition();

	float GetWorldRotation();

	Vector GetLocalPosition(){return transform.position;}

	float GetLocalRotation() {return transform.rotation; }

	void SetPosition(Vector pos){ transform.position = pos;}

	void SetRotation(float rot) { transform.rotation = rot; }

	void AddPosition(Vector delta) { transform.position += delta; }
	
	void AddRotation(float delta) { transform.rotation += delta; }
};


///支持场景变换的组件继承Component,使用时需要指针
///不支持场景变换的组件不继承Component,使用时不需要指针
///任何对象一定有场景变换，所以包含Component组件


//场景对象类（基类）
class Object
{
protected:
	Component* root;
	Object* parent = nullptr;
	set<Object*>sons;

	SpriteInfo aniSource;//动画源信息（用于记录并传递动画信息）

	void process_Destroy()
	{
		if (!sons.empty()) {
			for (auto it = sons.begin(); it != sons.end(); ++it)
				(*it)->process_Destroy();
		}
		GameObjects_.push_back(this);
	}

public:
	Object() { root = new Component; root->SetOwner(this);}
	virtual ~Object() { root->Destruct(); }
	
	virtual void Update() { ; }

	const SpriteInfo& GetAniSource() { return aniSource; }
	void SetAniSource(const SpriteInfo& info) { aniSource = info; }

	void SetAttachment(Object* par) {
		parent = par;
		par->sons.insert(this);
	}

	void UndoAttachment(Object* par) {
		SetPosition(GetWorldPosition());
		SetRotation(GetWorldRotation());
		parent = nullptr;
		par->sons.erase(this);
	}

	void Destroy()
	{
		if (parent)parent->sons.erase(this);

		process_Destroy();
	}
	

	Vector GetWorldPosition()
	{
		if (parent)
			return parent->GetWorldPosition() + GetLocalPosition();
		else
			return GetLocalPosition();
	}
	Vector GetLocalPosition() { return root->GetLocalPosition(); }
	void SetPosition(Vector pos) { root->SetPosition(pos); }
	void AddPosition(Vector delta) { root->AddPosition(delta); }
	float GetWorldRotation()
	{
		if (parent)
			return parent->GetWorldRotation() + GetLocalRotation();
		else
			return GetLocalRotation();
	}
	float GetLocalRotation() { return root->GetLocalRotation(); }
	void SetRotation(float rot) { root->SetRotation(rot); }
	void AddRotation(float delta) { root->AddRotation(delta); }
};



/* functions */

//获取指定整数范围随机数
extern int RandEx(int up, int down);

//类型转换
template<class T>
static T* Cast(Object*base)
{
	return dynamic_cast<T*>(base);
}
template<class T>
static T* Cast(Component* base)
{
	return dynamic_cast<T*>(base);
}


//游戏暂停
static void Pause()
{
	pauseTime = timeGetTime();
	pause = true;
	getimage(&pauseImage, 0, 0, WIN_WIDTH, WIN_HIGHT);
}

//取消暂停
static void Continue()
{
	DWORD deltaTime = timeGetTime() - pauseTime;
	for (auto it = GameLastTimes.begin(); it != GameLastTimes.end(); ++it)
	{
		*(*it) += deltaTime;
	}
	pause = false;
}