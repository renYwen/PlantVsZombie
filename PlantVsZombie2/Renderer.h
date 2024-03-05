#pragma once
#include"CoreMinimal.h"


//渲染组件
class SpriteRenderer :public Component
{
	SpriteInfo sprite;//渲染信息
	SpriteInfo_ sprite_;//渲染补充
	IMAGE en;//掩码图（仅用于静态图）
	bool bEn = false;//使用掩码图

	int layer = 0;//渲染层级
	BYTE transparency = 255;//透明度

	bool bIsUI = false;//渲染方式
	bool bFetchAni = true;//获取动画信息（如果有）

	IMAGE* copy = nullptr;//图像备份（便于调整图像大小）
	IMAGE copy_;//图像备份（便于旋转）

	float angle = 0;//临时寄存角度（一般不使用）
public:
	SpriteRenderer() { GameRenders.insert(this); }
	virtual ~SpriteRenderer() { GameRenders.erase(this); if (copy)delete copy; }


	virtual void Update() { 
		//UI的渲染组件没有Owner
		if (bFetchAni && GetOwner() && GetOwner()->GetAniSource().flag)
		{ 
			sprite = GetOwner()->GetAniSource(); 
		}
		if (transform.rotation != angle) {
			copy_ = RotateImage(sprite.image, double(transform.rotation));
			angle = transform.rotation;
		}
	}

	void Load(string name);//全局静态加载
	
	void Load(string path, int wid, int hei)//局部静态加载（耗性能,仅用于UI）
	{
		loadimage(sprite.image, LPCTSTR(path.c_str()), wid, hei);
	}

	void Load(string path, string path_en,int wid, int hei)//局部静态加载（包含掩码图，仅用于UI）
	{
		IMAGE buf;
		loadimage(&buf, LPCTSTR(path.c_str()), wid, hei);
		loadimage(&en, LPCTSTR(path_en.c_str()), wid, hei);
		bEn = true;

		sprite.image->Resize(wid,hei);
		SetWorkingImage(sprite.image);
		putimage(0, 0, &en, NOTSRCCOPY);
		putimage(0, 0, &buf, SRCPAINT);
		//临时绘制，不显示到屏幕上
		SetWorkingImage();
	}

	void SetLayer(int num) {
		GameRenders.erase(this);
		layer = num;
		GameRenders.insert(this);
	}
	int GetLayer()const { return layer; }
	
	void SetTransparency(BYTE tra) { transparency = tra; }
	BYTE GetTransparency() const { return transparency; }


	void SetUI(bool bUI) { bIsUI = bUI; }
	void SetFetchAni(bool bAni) { bFetchAni = bAni; }
	void SetFixEnable(bool en) { sprite_.isUsed = en; }
	void SetFixSize(Vector size) { sprite_.isUsed = true; sprite_.aimSize = size; }
	void SetFixLoc(Vector size) { sprite_.isUsed = true; sprite_.aimLoc = size; }
	void SetScale(Vector scale, string name); //仅用于静态图像

	void SetSprite(const SpriteInfo& sp) { sprite = sp; }
	void SetImage(IMAGE* buf) { sprite.image = buf; }
	void Render();


private:
	IMAGE RotateImage(IMAGE* pImg, double radian, COLORREF bkcolor = BLACK);//性能消耗较大，慎用
};


//静态网格类
class StaticMesh:public Object
{
protected:
	SpriteRenderer* renderer = nullptr;
public:
	StaticMesh();

	SpriteRenderer* GetRenderer() { return renderer; }
};