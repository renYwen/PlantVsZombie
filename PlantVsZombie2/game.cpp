
/* 头文件 */

//引擎(初始化创建基本对象以及遍历容器所需头文件)
#include "GameStatics.h"

#include "Renderer.h"
#include "Camera.h"
#include "BoxCollider.h"
#include "UserInterface.h"


//项目工程
#include "MenuController.h"



/* 编辑器变量 */
int collisionCount = 0;
bool bEdit = true;
IMAGE EditBg;
IMAGE Play;
IMAGE Play_;
bool flag = true;
bool flag_1 = true;

/* 初始化及编辑器函数 */

void Draw(IMAGE* image, int x, int y)//简易渲染函数
{
	HDC dstDC = GetImageHDC(NULL);
	HDC srcDC = GetImageHDC(image);
	int w = image->getwidth();
	int h = image->getheight();
	BLENDFUNCTION bf = { AC_SRC_OVER, 0, 255, AC_SRC_ALPHA };
	AlphaBlend(dstDC, x, y, w, h, srcDC, 0, 0, w, h, bf);
}

void Init()//初始化
{
	ifstream file;
	file.open("engine/file.txt", ios::in);
	if (file.is_open())
	{
		char buf[2];
		file >> buf;
		bEdit = atoi(buf);
	}
	file.close();
	//编辑器模式写入


	

	initgraph(WIN_WIDTH+200*bEdit, WIN_HIGHT, bEdit);
	//窗口创建

	setlinestyle(PS_SOLID | PS_JOIN_BEVEL);
	setfillcolor(LIGHTBLUE);
	setlinecolor(LIGHTBLUE);
	//系统Debug绘制参数

	setbkmode(TRANSPARENT);
	settextstyle(18, 10, "宋体");
	settextcolor(WHITE);
	//系统文字参数

	BeginBatchDraw();
	//绘图准备
}

void Start()//开始编辑器界面
{
	ExMessage msg;
	loadimage(&EditBg, "engine/background.png", WIN_WIDTH + 200, WIN_HIGHT);
	loadimage(&Play, "engine/play.jpg", 50, 50);
	loadimage(&Play_, "engine/play_.jpg", 50, 50);
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL, 2);
	while (true) {
		peekmessage(&msg);
		cleardevice();

		Draw(&EditBg, 0, 0);
		setfillcolor(DARKGRAY); fillrectangle(WIN_WIDTH, 0, WIN_WIDTH+200, WIN_HIGHT);
		if (msg.x > 375 && msg.x < 425 && msg.y > 25 && msg.y < 75) {
			Draw(&Play_, 375, 25); if (msg.lbutton)break;
		}
		else Draw(&Play, 375, 25);


		setfillcolor(LIGHTBLUE);
		fillrectangle(WIN_WIDTH + 75, 190, WIN_WIDTH + 125, 240);
		fillrectangle(WIN_WIDTH + 75, 390, WIN_WIDTH + 125, 440);

		settextstyle(18, 10, "宋体");
		outtextxy(WIN_WIDTH + 50, 150, "碰撞体显示");
		outtextxy(WIN_WIDTH + 25, 350, "控制台信息显示");

		settextstyle(35, 20, "宋体");
		if (collisionPattern)outtextxy(WIN_WIDTH+75, 200, "√");
		if (logPattern)outtextxy(WIN_WIDTH + 75, 400, "√");


		if (msg.message == WM_LBUTTONDOWN && flag && msg.x > WIN_WIDTH + 75  
			&& msg.x < WIN_WIDTH + 125 && msg.y > 190 && msg.y < 240) {
			collisionPattern = !collisionPattern; flag = false;
		}
		else if (msg.message == WM_LBUTTONUP)flag = true;
		
		if (msg.message == WM_LBUTTONDOWN && flag_1 && msg.x > WIN_WIDTH + 75 
			&& msg.x < WIN_WIDTH + 125 && msg.y > 390 && msg.y < 440) {
			logPattern = !logPattern; flag_1 = false;
		}
		else if (msg.message == WM_LBUTTONUP)flag_1 = true;



		FlushBatchDraw();
	}
}

void Edit()//编辑器模式边栏
{
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID | PS_JOIN_BEVEL,2);
	settextcolor(WHITE);

	setfillcolor(DARKGRAY); fillrectangle(WIN_WIDTH, 0, WIN_WIDTH + 200, WIN_HIGHT);
	const ExMessage &msg = MainController->GetCursorMessage();
	

	setfillcolor(LIGHTBLUE);
	fillrectangle(WIN_WIDTH + 75, 190, WIN_WIDTH + 125, 240);
	fillrectangle(WIN_WIDTH + 75, 390, WIN_WIDTH + 125, 440);

	settextstyle(18, 10, "宋体");
	outtextxy(WIN_WIDTH + 50, 150, "碰撞体显示");
	outtextxy(WIN_WIDTH + 25, 350, "控制台信息显示");

	settextstyle(35, 20, "宋体");
	if (collisionPattern)outtextxy(WIN_WIDTH + 75, 200, "√");
	if (logPattern)outtextxy(WIN_WIDTH + 75, 400, "√");


	if (msg.message == WM_LBUTTONDOWN && flag && msg.x > WIN_WIDTH + 75
		&& msg.x < WIN_WIDTH + 125 && msg.y > 190 && msg.y < 240) {
		collisionPattern = !collisionPattern; flag = false;
	}
	else if (msg.message == WM_LBUTTONUP)flag = true;

	if (msg.message == WM_LBUTTONDOWN && flag_1 && msg.x > WIN_WIDTH + 75
		&& msg.x < WIN_WIDTH + 125 && msg.y > 390 && msg.y < 440) {
		logPattern = !logPattern; flag_1 = false;
	}
	else if (msg.message == WM_LBUTTONUP)flag_1 = true;
}

/* 主循环逻辑函数 */

void Info(DWORD interval)//控制台全局信息(ms)
{
	static DWORD lastTime = timeGetTime();
	static DWORD startTime = timeGetTime();
	if (timeGetTime() - lastTime >= interval) {
		if (logPattern) {
			printf("Time: %.3f  ", float(timeGetTime() - startTime) / 1000);
			cout << "Objects: " << GameObjects.size() << " ";
			cout << "Components: " << GameComponents.size() << " ";
			cout << "Renders: " << GameRenders.size() << " ";
			cout << "Colliders: " << GameColliders.size() << " " << endl;
			if (collisionPattern)
				cout << "Collisons Calculations :  " << collisionCount << endl;
		}
		lastTime = timeGetTime();
	}
}

void Input()//输入
{
	MainController->PeekInfo();
}

void Render()//渲染
{
	cleardevice();

	if (!pause) {
		
		for (auto it = GameRenders.begin(); it != GameRenders.end(); ++it)
		{
			(*it)->Render();
		}
		
		for (auto it = GamePainters.begin(); it != GamePainters.end(); ++it)
		{
			(*it)->Paint();
		}
		
		if (collisionPattern && bEdit) {
			setlinecolor(RGB(255, 165, 0));
			setlinestyle(PS_SOLID | PS_JOIN_BEVEL,2);
			for (int i = 1; i < 6; i++) line(0,100*i,800,100*i);
			for (int j = 1;j < 8;j++) line(j*100,0,j*100,600);
			
			for (auto it = GameColliders.begin(); it != GameColliders.end(); ++it)
			{
				(*it)->DrawDebugLine(2);
			}
		}
	}
	else putimage(0,0, &pauseImage);
	
	if (bEdit)Edit();

	FlushBatchDraw();
}

void Update()//对象及组件更新或删除
{
	if (!pause) {
		
		vector<BoxCollider*>arr[8][6];
		for (auto& arr_i : arr)
			for (auto& arr_j : arr_i)
				arr_j.reserve(GameColliders.size());


		for (auto it = GameColliders.begin(); it != GameColliders.end(); ++it)
		{
			(*it)->Clear();
		
			Vector pos = (*it)->GetWorldPosition();
			int x = int(pos.x) / 100; if (x < 0)x = 0; if (x > 7)x = 7;
			int y = int(pos.y) / 100; if (y < 0)y = 0; if (y > 5)y = 5;
			pos += (*it)->GetSize();
			int x_1 = int(pos.x) / 100; if (x_1 < 0)x_1 = 0; if (x_1 > 7)x_1 = 7;
			int y_1 = int(pos.y) / 100; if (y_1 < 0)y_1 = 0; if (y_1 > 5)y_1 = 5;

			for (int i = x; i <= x_1; ++i)
				for (int j = y; j <= y_1; ++j)
					arr[i][j].push_back(*it);
		}
		collisionCount = 0;
		for (auto&arr_i:arr){
			for (auto& arr_j : arr_i){
				if (!arr_j.empty()){
					for (auto me = arr_j.begin(); me != arr_j.end(); ++me){
						for (auto he = arr_j.begin(); he != arr_j.end(); ++he)
							if (he != me) { (*me)->Insert(*he); ++collisionCount; }
					}
				}
			}
		}
		//碰撞信息更新
		
		
		set<Object*>::iterator it;
		for (it = GameObjects.begin(); it != GameObjects.end(); ++it)
		{
			(*it)->Update();if(changeLevel)break;
		}
		//对象更新
		changeLevel = false;
		set<Component*>::iterator it1;
		for (it1 = GameComponents.begin(); it1 != GameComponents.end(); ++it1)
		{
			(*it1)->Update(); if(changeLevel)break;
		}
		//组件更新
		changeLevel = false;
		for (auto it = GameUIs.begin(); it != GameUIs.end(); ++it)
		{
			(*it)->Update(); if(changeLevel)break;
		}
		//UI更新
		changeLevel = false;

		

		if (!GameObjects_.empty()) {
			vector<Object*>::iterator it_;
			for (it_ = GameObjects_.begin(); it_ != GameObjects_.end(); ++it_)
			{
				GameObjects.erase(*it_);
				delete* it_;
			}
			GameObjects_.clear();
		}
		//对象删除
		if (!GameComponents_.empty()) {
			vector<Component*>::iterator it1_;
			for (it1_ = GameComponents_.begin(); it1_ != GameComponents_.end(); ++it1_)
			{
				GameComponents.erase(*it1_);
				delete* it1_;
			}
			GameComponents_.clear();
		}
		//组件删除
		if (!GameComponents_.empty()) {
			vector<Component*>::iterator it1_;
			for (it1_ = GameComponents_.begin(); it1_ != GameComponents_.end(); ++it1_)
			{
				GameComponents.erase(*it1_);
				delete* it1_;
			}
			GameComponents_.clear();
		}
		//UI删除
		if (!GameUIs_.empty()) {
			for (auto it = GameUIs_.begin(); it != GameUIs_.end(); ++it)
			{
				GameUIs.erase(*it);
				delete* it;
			}
			GameUIs_.clear();
		}
	}
	else
	{
		MainController->Update();
	}//暂停状态下，玩家控制器仍然可用
}



//游戏主循环
void CALLBACK timecallback(UINT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR)
{
	Input();
	if(bEdit)Info(250);
	Update();
	Render();
}


//输入
void CALLBACK timecallback1(UINT, UINT, DWORD_PTR, DWORD_PTR, DWORD_PTR)
{
	Input();
}




[[noreturn]] int main()
{
	Init();
	if(bEdit)Start();

	MainCamera = GameStatics::ConstructComponent<Camera>(Vector(0, 0));
	MainController = GameStatics::CreateObject<AMenuController>(Vector(0, 0));

	

	timeSetEvent(DWORD(DELTA_TIME * 1000), 1, timecallback, NULL, TIME_CALLBACK_FUNCTION | TIME_PERIODIC);//TIME_KILL_SYNCHRONOUS
	timeSetEvent(2, 1, timecallback1, NULL, TIME_CALLBACK_FUNCTION | TIME_PERIODIC);//TIME_KILL_SYNCHRONOUS

	Sleep(INFINITE);
}

