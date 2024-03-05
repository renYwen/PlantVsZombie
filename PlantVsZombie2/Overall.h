/* variable（游戏全局变量） */


#pragma once

#include<set>
#include<vector>
#include<map>
#include<stack>

#define WIN_WIDTH 800
#define WIN_HIGHT 600

#define DELTA_TIME 0.01f

#define ROW_WIDTH 80
#define COLUMN_HIGHT 100

/* 由于需要指定某一值（地址）进行查找并删除操作，线性查找开销较大，
故使用树形set存储，单次增删时间复杂度都为O（logN） */

//游戏对象实例
extern std::set<class Object*>GameObjects;

//游戏组件实例
extern std::set<class Component*>GameComponents;


/* 由于只需要进行线性存储和线性删除，故使用vector存储，
单次时间复杂度为O（1），总时间复杂度为O（N） */

//游戏对象删除数组
extern std::vector<class Object*>GameObjects_;

//游戏组件删除数组
extern std::vector<class Component*>GameComponents_;


/* 由于需要严格有序以便于按照层级渲染，且层级完全可以重复，
所以比较时额外引入地址值作为层级相同时的比较，且使用set存储，
单次插入删除时时间复杂度为O（logN），渲染时总时间复杂度为0（N）*/

//游戏渲染组件
extern bool cmp(class SpriteRenderer*a,class SpriteRenderer*b);
extern std::set<class SpriteRenderer*,decltype(&cmp)>GameRenders;

//游戏文字绘图组件
extern std::set<class Widget*>GamePainters;


//游戏碰撞组件(每个组件都要进行碰撞判断，总时间复杂度为O（N^2）)
extern std::set<class BoxCollider*>GameColliders;


//游戏UI组件
extern std::set<class UserInterface*>GameUIs;

//游戏UI删除数组
extern std::vector<class UserInterface*>GameUIs_;


//玩家控制器（处理玩家输入输出操作，全局只有一个）
extern class Controller* MainController;

//游戏主相机（组件一般不能独立存在，游戏主相机比较特殊，因为其生命周期一般为全局，且只有一个）
extern class Camera* MainCamera;

//场景切换
extern bool changeLevel;

//游戏计时器lastTime地址
extern std::set<DWORD*>GameLastTimes;
//游戏暂停时间记录
extern DWORD pauseTime;
//游戏暂停背景图片
extern class IMAGE pauseImage;
//游戏暂停
extern bool pause;



//开发者模式
extern bool logPattern;

//碰撞体显示
extern bool collisionPattern;

//资源池（全局仅有一个）
extern class Resources ResourcePool;