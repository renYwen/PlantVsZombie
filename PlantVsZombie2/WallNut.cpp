#include "WallNut.h"


AWallNut::AWallNut()
{
	name = Nut;
	type = Protector;
	price = 50;

	temp.Load("wallnut",6, 6, 32);
	temp.SetInterval(0.06f);
	temp_1.Load("wallnut_1", 11, 1, 11, {10,3});
	temp_1.SetInterval(0.12f);
	temp_2.Load("wallnut_2", 6, 6, 32);
	temp_2.SetInterval(0.06f);


	ani->Insert("idle", temp);
	ani->Insert("crack", temp_1);
	ani->Insert("crack_", temp_2);
	ani->SetNode("idle");

	blood = 125;
}

void AWallNut::Update()
{
	APlant::Update();

	if (blood < 80 && !crackFlag) {
		ani->SetNode("crack"); crackFlag = 1;
	}
	else if (blood < 40 && crackFlag==1)
	{
		ani->SetNode("crack_"); crackFlag = 2;
	}
}
