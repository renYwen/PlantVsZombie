#pragma once
#include "UserInterface.h"
#include "Timer.h"

class UBattleUI :public UserInterface
{
	friend class ABattleController;
	Text* text;

	Image* SeedBank;
	Image* Seeds[8];
	int prices[8] = { 100,50,150,50,25,175,150,200 };

	Image* StartTitle0; Image* StartTitle1; Image* StartTitle2;
	Image* Warning;Image* FinalWarning;

	Image* EmptyBar; Image* FullBar; Image* Level;
	Image* Flag[3]; Image* Head; 
	Image* Blank; Image* Scoop; bool scoopFlag = false;

	Image* Blood; Image* Blood_1;

	Image* Gray[8];
	Image* Black[8];
	Timer<UBattleUI>timers[8];
	float coolingTime[8] = { 5,5,45,30,30,5,5,5 };
	//float coolingTime[8] = { 0,0,0,0,0,0,0,0 };/* for Debug */

	Text* Money;

	/* 控制器与ui通信 */
	bool bStart = false;//游戏正式开始
	string sunNum;//阳光值
	int index = -1;//创建植物下标值
	int failFlag = 0;//点击植物失败
public:
	UBattleUI()
	{
		text = AddWidget<Text>(Vector(250, 500));
		text->SetSize(Vector(100, 50));
		text->SetText("$0阿婆主的豪宅", 7);

		EmptyBar = AddWidget<Image>(Vector(575, 575));
		EmptyBar->SetSize(Vector(157, 21));
		EmptyBar->LoadPicture("res/images/FlagMeterEmpty.png");
		EmptyBar->SetLayer(15);
		FullBar = AddWidget<Image>(Vector(732, 575));
		FullBar->SetSize(Vector(157, 21));
		FullBar->LoadPicture("res/images/FlagMeterFull.png");
		FullBar->SetLayer(16);
		Level = AddWidget<Image>(Vector(610, 590));
		Level->SetSize(Vector(86, 11));
		Level->LoadPicture("res/images/FlagMeterLevelProgress.png");
		Level->SetLayer(18);
		Head = AddWidget<Image>(Vector(600, 600));
		Head->SetSize(Vector(22, 23));
		Head->LoadPicture("res/images/FlagMeterParts1.png");
		Head->SetLayer(19);
		Blood = AddWidget<Image>(Vector(100, 525));
		Blood->SetSize(Vector(432, 28));
		Blood->LoadPicture("res/images/blood.png");
		Blood->SetLayer(20);
		Blood_1 = AddWidget<Image>(Vector(110, 527));
		Blood_1->SetSize(Vector(412, 24));
		Blood_1->LoadPicture("res/images/blood_1.png");
		Blood_1->SetLayer(21);


		Flag[0] = AddWidget<Image>(Vector(695, 575));
		Flag[1] = AddWidget<Image>(Vector(635, 575));
		Flag[2] = AddWidget<Image>(Vector(600, 575));
		for (int i = 0;i<3;i++)
		{
			Flag[i]->SetSize(Vector(20, 18));
			Flag[i]->LoadPicture("res/images/FlagMeterParts2.png");
			Flag[i]->SetLayer(17);
		}


		Blank = AddWidget<Image>(Vector(536, 0));
		Blank->SetSize(Vector(70, 72));
		Blank->LoadPicture("res/images/blank.png");
		Blank->SetLayer(-2);
		Scoop = AddWidget<Image>(Vector(536, 0));
		Scoop->SetSize(Vector(70, 72));
		Scoop->LoadPicture("res/images/scoop.png");
		Scoop->SetLayer(-1);


		StartTitle0 = AddWidget<Image>(Vector(300, 250));
		StartTitle0->SetSize(Vector(225, 93));
		StartTitle0->LoadPicture("res/images/READYTO.png");
		StartTitle0->SetLayer(15);
		StartTitle1 = AddWidget<Image>(Vector(300, 250));
		StartTitle1->SetSize(Vector(163, 60));
		StartTitle1->LoadPicture("res/images/PUT.png");
		StartTitle1->SetLayer(15);
		StartTitle2 = AddWidget<Image>(Vector(300, 250));
		StartTitle2->SetSize(Vector(234,110));
		StartTitle2->LoadPicture("res/images/YOURPLANT.png");
		StartTitle2->SetLayer(15);

		Warning = AddWidget<Image>(Vector(180, 250));
		Warning->SetSize(Vector(468, 54));
		Warning->LoadPicture("res/images/warning.png");
		Warning->SetLayer(15);
		FinalWarning = AddWidget<Image>(Vector(200, 250));
		FinalWarning->SetSize(Vector(468, 126));
		FinalWarning->LoadPicture("res/images/lastwarning.png");
		FinalWarning->SetLayer(15);
	

		SeedBank = AddWidget<Image>(Vector(5,-120));
		SeedBank->SetSize(Vector(530, 91));
		SeedBank->LoadPicture("res/images/bar.png");
		SeedBank->SetLayer(-3);

		Money = AddWidget<Text>(Vector(22, 65));
		Money->SetAttachment(SeedBank);
		Money->SetSize(Vector(100, 50));
		Money->SetText("100", 4);
		Money->BindText(sunNum);

		int wid = 53;
		int hei = 77;
		char cardname[50];
		for (int i = 0;i<8;++i)
		{
			Gray[i] = AddWidget<Image>(Vector(80 + (wid + 2) * i, 6));
			Gray[i]->SetAttachment(SeedBank);
			Gray[i]->SetSize(Vector(wid, hei));
			Gray[i]->LoadPicture("res/images/cards/black.png");
			Gray[i]->SetTrans(125);
			Gray[i]->SetLayer(-1);

			Black[i] = AddWidget<Image>(Vector(80 + (wid + 2) * i, 6));
			Black[i]->SetAttachment(SeedBank);
			Black[i]->SetSize(Vector(wid, hei));
			Black[i]->LoadPicture("res/images/cards/black.png");
			Black[i]->SetTrans(125);

			Seeds[i] = AddWidget<Image>(Vector(80+(wid+2)*i, 6));
			Seeds[i]->SetAttachment(SeedBank);
			Seeds[i]->SetSize(Vector(wid, hei));
				
			sprintf_s(cardname, sizeof(cardname), "res/images/cards/card%d.png", i+1);
			Seeds[i]->LoadPicture(cardname);
			Seeds[i]->SetLayer(-2);
		}
	
	}

	void Update();

	void ResetText();
};