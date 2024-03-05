#pragma once
#include "UserInterface.h"
#include "Timer.h"



class UMenuUI :public UserInterface
{
	friend class AMenuController;
	Image* Logo;
	int count = 2;
	Image* LoadingBg;
	Image* LoadBar;
	Image* LoadBar_1;
	Button* LoadBar_2;
	Text* LoadText;
	Image* Roll;

	Image* SkyBg;
	Image* FarBg;
	Image* MiddleBg;
	Image* NearBg;
	Image* Clouds[6];

	Button* Adventure;
	Button* Quit;
	Image* Grass;
	Image* WoodSign;
	Image* Leaf;
	int isReady = 0;
public:
	UMenuUI()
	{
		Logo = AddWidget<Image>(Vector(250, 150));
		Logo->SetSize(Vector(300, 300));
		Logo->LoadPicture("res/images/Logo.png");
		Logo->SetTrans(count);
		Logo->SetLayer(5);
		
		
		LoadingBg = AddWidget<Image>(Vector(0, 0));
		LoadingBg->SetSize(Vector(800, 600));
		LoadingBg->LoadPicture("res/images/loadingbg.png");


		LoadText = AddWidget<Text>(Vector(315, 465));
		LoadText->SetSize(Vector(400, 75));
		LoadText->SetText("$7Loading......", 4);
		LoadText->SetPattern(2);

		LoadBar = AddWidget<Image>(Vector(167, 445));
		LoadBar->SetSize(Vector(482, 80));
		LoadBar->LoadPicture("res/images/LoadBar.png");
		LoadBar->SetLayer(1);
		LoadBar_1 = AddWidget<Image>(Vector(155, 387));
		LoadBar_1->SetSize(Vector(498, 78));
		LoadBar_1->LoadPicture("res/images/LoadBar_1.png");
		LoadBar_1->SetLayer(2);
		LoadBar_1->SetPicSize(Vector(0,75));

		LoadBar_2 = AddWidget<Button>(Vector(165, 425));
		LoadBar_2->SetSize(Vector(470, 80));

		Roll = AddWidget<Image>(Vector(130, 390));
		Roll->SetSize(Vector(73, 71));
		Roll->LoadPicture("res/images/SodRollCap.png");
		Roll->SetLayer(3);


		SkyBg = AddWidget<Image>(Vector(0, 0));
		SkyBg->SetSize(Vector(850, 600));
		SkyBg->LoadPicture("res/images/Menu/SelectorScreen_BG.jpg");
		SkyBg->SetLayer(-1);

		FarBg = AddWidget<Image>(Vector(50, 310));
		FarBg->SetSize(Vector(720, 350));
		FarBg->LoadPicture("res/images/Menu/SelectorScreen_BG_Center.jpg", "res/images/Menu/SelectorScreen_BG_Center_.png");
		FarBg->SetLayer(1);

		MiddleBg = AddWidget<Image>(Vector(0, 0));
		MiddleBg->SetSize(Vector(480, 710));
		MiddleBg->LoadPicture("res/images/Menu/SelectorScreen_BG_Left.jpg", "res/images/Menu/SelectorScreen_BG_Left_.png");
		MiddleBg->SetLayer(2);


		NearBg = AddWidget<Image>(Vector(70, 580));
		NearBg->SetSize(Vector(730, 560));
		NearBg->LoadPicture("res/images/Menu/SelectorScreen_BG_Right.png");
		NearBg->SetLayer(3);

		Clouds[0]= AddWidget<Image>(Vector(0, 75)); Clouds[0]->SetSize(Vector(220, 206));
		Clouds[1] = AddWidget<Image>(Vector(400, 25)); Clouds[1]->SetSize(Vector(152, 121));
		Clouds[2] = AddWidget<Image>(Vector(700, 50)); Clouds[2]->SetSize(Vector(239, 91));
		Clouds[3] = AddWidget<Image>(Vector(1000, 100)); Clouds[3]->SetSize(Vector(434,144));
		Clouds[4] = AddWidget<Image>(Vector(1300, 125)); Clouds[4]->SetSize(Vector(76,44));
		Clouds[5] = AddWidget<Image>(Vector(1250, 50)); Clouds[5]->SetSize(Vector(211,73));
		char cardname[75];
		for (int i = 0; i < 6; ++i)
		{
			sprintf_s(cardname, sizeof(cardname), "res/images/Menu/SelectorScreen_Cloud%d.png", i + 1);
			Clouds[i]->LoadPicture(cardname);
		}

		Grass = AddWidget<Image>(Vector(-70, 498));
		Grass->SetAttachment(NearBg);
		Grass->SetSize(Vector(240,62));
		Grass->LoadPicture("res/images/Menu/SelectorScreen_Leaves.png");
		Grass->SetLayer(4);

		Leaf = AddWidget<Image>(Vector(130, 525));
		Leaf->SetAttachment(NearBg);
		Leaf->SetSize(Vector(40, 40));
		Leaf->LoadPicture("res/images/Menu/SelectorScreen_Leaf1.png");
		Leaf->SetLayer(5);

		Adventure = AddWidget<Button>(Vector(333, 30));
		Adventure->SetAttachment(NearBg);
		Adventure->SetSize(Vector(331,145));
		Adventure->LoadPicture("res/images/Menu/Adventure.png");
		Adventure->LoadHoverPicture("res/images/Menu/Adventure_1.png");
		Adventure->LoadClickPicture("res/images/Menu/Adventure.png");
		Adventure->SetLayer(5);

		Quit = AddWidget<Button>(Vector(645, 460));
		Quit->SetAttachment(NearBg);
		Quit->SetSize(Vector(50,30));
		Quit->LoadPicture("res/images/Menu/SelectorScreen_Quit1.png");
		Quit->LoadHoverPicture("res/images/Menu/SelectorScreen_Quit2.png");
		Quit->LoadClickPicture("res/images/Menu/SelectorScreen_Quit1.png");
		Quit->SetLayer(5);

		WoodSign = AddWidget<Image>(Vector(25, -150));
		WoodSign->SetSize(Vector(293, 150));
		WoodSign->LoadPicture("res/images/WoodSign.png");
		WoodSign->SetLayer(3);
	}

	void Update();
};