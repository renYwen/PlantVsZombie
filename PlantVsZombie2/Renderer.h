#pragma once
#include"CoreMinimal.h"


//��Ⱦ���
class SpriteRenderer :public Component
{
	SpriteInfo sprite;//��Ⱦ��Ϣ
	SpriteInfo_ sprite_;//��Ⱦ����
	IMAGE en;//����ͼ�������ھ�̬ͼ��
	bool bEn = false;//ʹ������ͼ

	int layer = 0;//��Ⱦ�㼶
	BYTE transparency = 255;//͸����

	bool bIsUI = false;//��Ⱦ��ʽ
	bool bFetchAni = true;//��ȡ������Ϣ������У�

	IMAGE* copy = nullptr;//ͼ�񱸷ݣ����ڵ���ͼ���С��
	IMAGE copy_;//ͼ�񱸷ݣ�������ת��

	float angle = 0;//��ʱ�Ĵ�Ƕȣ�һ�㲻ʹ�ã�
public:
	SpriteRenderer() { GameRenders.insert(this); }
	virtual ~SpriteRenderer() { GameRenders.erase(this); if (copy)delete copy; }


	virtual void Update() { 
		//UI����Ⱦ���û��Owner
		if (bFetchAni && GetOwner() && GetOwner()->GetAniSource().flag)
		{ 
			sprite = GetOwner()->GetAniSource(); 
		}
		if (transform.rotation != angle) {
			copy_ = RotateImage(sprite.image, double(transform.rotation));
			angle = transform.rotation;
		}
	}

	void Load(string name);//ȫ�־�̬����
	
	void Load(string path, int wid, int hei)//�ֲ���̬���أ�������,������UI��
	{
		loadimage(sprite.image, LPCTSTR(path.c_str()), wid, hei);
	}

	void Load(string path, string path_en,int wid, int hei)//�ֲ���̬���أ���������ͼ��������UI��
	{
		IMAGE buf;
		loadimage(&buf, LPCTSTR(path.c_str()), wid, hei);
		loadimage(&en, LPCTSTR(path_en.c_str()), wid, hei);
		bEn = true;

		sprite.image->Resize(wid,hei);
		SetWorkingImage(sprite.image);
		putimage(0, 0, &en, NOTSRCCOPY);
		putimage(0, 0, &buf, SRCPAINT);
		//��ʱ���ƣ�����ʾ����Ļ��
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
	void SetScale(Vector scale, string name); //�����ھ�̬ͼ��

	void SetSprite(const SpriteInfo& sp) { sprite = sp; }
	void SetImage(IMAGE* buf) { sprite.image = buf; }
	void Render();


private:
	IMAGE RotateImage(IMAGE* pImg, double radian, COLORREF bkcolor = BLACK);//�������Ľϴ�����
};


//��̬������
class StaticMesh:public Object
{
protected:
	SpriteRenderer* renderer = nullptr;
public:
	StaticMesh();

	SpriteRenderer* GetRenderer() { return renderer; }
};