#include "MenuUI.h"
#include "GameStatics.h"
#include "BattleController.h"


void UMenuUI::Update()
{
	UserInterface::Update();

	if (count > 0)
	{
		static bool flag = false;
		flag ? count-=2 : count+=2;
		Logo->SetTrans(count>255?255:count);
		if (count >= 400)flag = true;

		if (count == 2) {
			LoadingBg->SetVisibility(true);
			LoadBar->SetVisibility(true);
			LoadBar_1->SetVisibility(true);
			Roll->SetVisibility(true);
			LoadText->SetVisibility(true);
		}
	}
	else{
		static int num = 0;
		if (num < 482) LoadBar_1->SetPicSize(Vector(num += 2, 75));
		else { 
			LoadBar_1->SetPicSize(Vector(498, 78)); LoadBar_2->SetVisibility(true);
		    LoadText->SetText("$7Click To Start", 4);
		}


		Roll->SetLocation(Vector(125 + num, 390 + num / 10));
		Roll->SetScale(Vector(73 - num / 10, 71 - num / 10));
		if (num > 470)Roll->SetVisibility(false);
	}

	if (LoadBar_2->IsCursorOn())
		LoadText->SetText("$9Click To Start", 4);
	if (LoadBar_2->IsCursorUp())
	{
		LoadingBg->SetVisibility(false);
		LoadBar->SetVisibility(false);
		LoadBar_1->SetVisibility(false);
		LoadBar_2->SetVisibility(false);
		LoadText->SetVisibility(false);

		SkyBg->SetVisibility(true);
		FarBg->SetVisibility(true);
		MiddleBg->SetVisibility(true);
		NearBg->SetVisibility(true);
		Grass->SetVisibility(true);
		Leaf->SetVisibility(true);
		for (auto&arr:Clouds)arr->SetVisibility(true);
		
		Quit->SetVisibility(true);
		Adventure->SetVisibility(true);
		WoodSign->SetVisibility(true);
	}

	if (Adventure->IsCursorOn() && !isReady)isReady = 1;
	else if (Adventure->IsCursorClicked())isReady = 2;
	else if (!Adventure->IsCursorOn())isReady = 0;

	if (Quit->IsCursorClicked())exit(0);

	if (Leaf->GetVisibility()) {
		static float dir = 0.002f;
		if (Leaf->GetRotation() > 0.3f)dir = -0.002f;
		if (Leaf->GetRotation() < 0)dir = 0.002f;
		Leaf->AddRotation(dir); 
	}

	for (int i = 0; i < 6; ++i)
	{
		Vector pos = Clouds[i]->GetAbsoluteLocation();
		if (pos.x < -800)pos.x = 800;
		Clouds[i]->SetLocation(pos + Vector(-0.2f - 0.02f * i, 0));
	}
}
