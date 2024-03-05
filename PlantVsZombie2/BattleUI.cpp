#include "BattleUI.h"
#include "BattleController.h"


void UBattleUI::Update()
{
	UserInterface::Update();

	if (!bStart)return;

	ResetText();

	ABattleController* pController = Cast<ABattleController>(MainController);
	
	index = -1;
	for (int i = 0;i<8;++i)
	{
		if (Seeds[i]->IsCursorOn()) {
			if (prices[i] <= pController->sunShine && timers[i].GetDelay() >= coolingTime[i])
			{
				index = i; break;
			}
			else if (MainController->GetCursorMessage().lbutton)
			{
				failFlag = 1;
				if (prices[i] > pController->sunShine)failFlag = 2;
				break;
			}
		}	
	}

	for (int i = 0; i < 8; ++i)
	{
		if (prices[i] > pController->sunShine || timers[i].GetDelay() < coolingTime[i])
			Gray[i]->SetTrans(125);
		else Gray[i]->SetTrans(0);
	}

	for (int i = 0; i < 8; ++i)
	{
		if (timers[i].GetDelay() < coolingTime[i])
		{
			Black[i]->SetPicSize(Vector(Black[i]->GetSize().x,
				Black[i]->GetSize().y * (1-timers[i].GetDelay() /coolingTime[i])));
		}
	}


}

void UBattleUI::ResetText()
{
	ABattleController* pController = Cast<ABattleController>(MainController);

	if(timers[0].GetDelay() < coolingTime[0])
		Seeds[0]->SetInfoText("豌豆射手\n$9冷却中");
	else if(prices[0] > pController->sunShine)
		Seeds[0]->SetInfoText("豌豆射手\n$9没有足够阳光");
	else
		Seeds[0]->SetInfoText("豌豆射手");

	if (timers[1].GetDelay() < coolingTime[1])
		Seeds[1]->SetInfoText("向日葵\n$9冷却中");
	else if (prices[1] > pController->sunShine)
		Seeds[1]->SetInfoText("向日葵\n$9没有足够阳光");
	else
		Seeds[1]->SetInfoText("向日葵");

	if (timers[2].GetDelay() < coolingTime[2])
		Seeds[2]->SetInfoText("樱桃炸弹\n$9冷却中");
	else if (prices[2] > pController->sunShine)
		Seeds[2]->SetInfoText("樱桃炸弹\n$9没有足够阳光");
	else
		Seeds[2]->SetInfoText("樱桃炸弹");

	if (timers[3].GetDelay() < coolingTime[3])
		Seeds[3]->SetInfoText("坚果\n$9冷却中");
	else if (prices[3] > pController->sunShine)
		Seeds[3]->SetInfoText("坚果\n$9没有足够阳光");
	else
		Seeds[3]->SetInfoText("坚果");

	if (timers[4].GetDelay() < coolingTime[4])
		Seeds[4]->SetInfoText("土豆地雷\n$9冷却中");
	else if (prices[4] > pController->sunShine)
		Seeds[4]->SetInfoText("土豆地雷\n$9没有足够阳光");
	else
		Seeds[4]->SetInfoText("土豆地雷");

	if (timers[5].GetDelay() < coolingTime[5])
		Seeds[5]->SetInfoText("寒冰射手\n$9冷却中");
	else if (prices[5] > pController->sunShine)
		Seeds[5]->SetInfoText("寒冰射手\n$9没有足够阳光");
	else
		Seeds[5]->SetInfoText("寒冰射手");

	if (timers[6].GetDelay() < coolingTime[6])
		Seeds[6]->SetInfoText("食人花\n$9冷却中");
	else if (prices[6] > pController->sunShine)
		Seeds[6]->SetInfoText("食人花\n$9没有足够阳光");
	else
		Seeds[6]->SetInfoText("食人花");

	if (timers[7].GetDelay() < coolingTime[7])
		Seeds[7]->SetInfoText("双发射手\n$9冷却中");
	else if (prices[7] > pController->sunShine)
		Seeds[7]->SetInfoText("双发射手\n$9没有足够阳光");
	else
		Seeds[7]->SetInfoText("双发射手");
}
