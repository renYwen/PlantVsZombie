#include "BattleController.h"
#include "BasePlant.h"
#include "BattleUI.h"
#include "GameStatics.h"
#include "Audio.h"
#include "RigidBody.h"
#include "Camera.h"

#include "PeaShooter.h"
#include "SunFlower.h"
#include "CherryBomb.h"
#include "WallNut.h"
#include "Mine.h"
#include "Chomper.h"
#include "IceShooter.h"
#include "DoubleShooter.h"

#include "Sun.h"
#include "Car.h"
#include "Grow.h"
#include "Split.h"
#include "Split_.h"

#include "NormalStand.h"
#include "HatStand.h"
#include "NormalZombie.h"
#include "HatZombie.h"
#include "BucketZombie.h"
#include "ArmorZombie.h"
#include "JumpZombie.h"
#include "BossZombie.h"

extern APlant* plants[9][5]{};
extern int zombieNumPerRow[5] = { 0 };

float generateTime[80] = { 32,52,72,90,110,125,140,152,160,170,180,195,/* 第1波 */
	200,210,215,218,220,222,224,228,/* 精英僵尸 */
	240,250,258,265,275,282,290,295,300,305,310,318,322,330,335,339,345,350,355,360,365,370,375,380,/* 第2波 */
	385,395,399,401,402,404,406,408,410,415,419,423,427,430,435,440,/* 第3波 */
	445,450,455,459,460,462,464,466,468,470,473,475,479,485,490,495,500,502,510,520
};


ABattleController::ABattleController()
{
	ui = GameStatics::CreateUI<UBattleUI>();
	ui->ShowOnScreen();
	ui->StartTitle0->SetVisibility(false);
	ui->StartTitle1->SetVisibility(false);
	ui->StartTitle2->SetVisibility(false);
	ui->Level->SetVisibility(false);
	ui->EmptyBar->SetVisibility(false);
	ui->FullBar->SetVisibility(false);
	ui->Head->SetVisibility(false);
	ui->Scoop->SetVisibility(false);
	ui->Blank->SetVisibility(false);
	ui->Warning->SetVisibility(false);
	ui->FinalWarning->SetVisibility(false);
	ui->Blood->SetVisibility(false);
	ui->Blood_1->SetVisibility(false);
	
	for(int i=0;i<3;i++)ui->Flag[i]->SetVisibility(false);
		
	player = GameStatics::ConstructComponent<AudioPlayer>(Vector(0,0));
	player->SetAttachment(root);
	
	
	MainCamera->SetPosition(Vector(-225,0));

	BossGenerateTimeHandle.Bind(3.5f, &ABattleController::Generate_, this, true);
	SunTimeHandle.Bind(8.f, &ABattleController::Produce, this, true);
}

void ABattleController::Update()
{
	Controller::Update();

	/* 动画部分 */
	static StaticMesh* bg1 = nullptr;
	static StaticMesh* bg3 = nullptr;
	static AudioPlayer* player_ = nullptr;
	//开场
	if (bAniFlag)
	{
		static StaticMesh* bg0 = nullptr;
		static StaticMesh* roll = nullptr;
		static StaticMesh* rollCap = nullptr;
		float time = AnimationTimeHandle.GetDelay();
		if (time == 0) {
			player_ = GameStatics::ConstructComponent<AudioPlayer>(Vector(0, 0));
			player_->SetAttachment(root);
			AudioSource bgm("res/sounds/chooseyourseeds.mp3");
			player_->Play(bgm);
			bg0 = GameStatics::CreateObject<StaticMesh>(Vector(-225, 0));
			bg0->GetRenderer()->Load("bg0");
			bg0->GetRenderer()->SetLayer(-8);

			
			GameStatics::CreateObject<ANormalStand>(Vector(825,50));
			GameStatics::CreateObject<ANormalStand>(Vector(750, 180));
			GameStatics::CreateObject<AHatStand>(Vector(815, 225));
			GameStatics::CreateObject<AHatStand>(Vector(975, 425));
			GameStatics::CreateObject<ANormalStand>(Vector(925, 300));
			GameStatics::CreateObject<ANormalStand>(Vector(950, 200));
			GameStatics::CreateObject<ANormalStand>(Vector(850, 400));
		}

		if (MainCamera->GetLocalPosition().x > 150)
			ui->text->SetVisibility(false);
		
		if(time >= 2.f && time < 2.1f)
			MainCamera->MoveTo(Vector(375, 0), 1.75f);
		else if (time >= 6.f && time < 6.1f)
			MainCamera->MoveTo(Vector(0, 0), 1.f);
		else if (time >= 8.f) {
			static int num = 0;
			if (rollPattern == 0) {
				AudioSource bgm("res/sounds/roll.mp3");
				player->Play(bgm,true);
				roll = GameStatics::CreateObject<StaticMesh>(Vector(10, 240));
				roll->GetRenderer()->Load("roll");
				roll->GetRenderer()->SetLayer(-4);
				rollCap = GameStatics::CreateObject<StaticMesh>(Vector(8, 328));
				rollCap->GetRenderer()->Load("rollCap");
				rollCap->GetRenderer()->SetLayer(-3);
				bg1 = GameStatics::CreateObject<StaticMesh>(Vector(-225, 0));
				bg1->GetRenderer()->Load("bg1");
				bg1->GetRenderer()->SetLayer(-7);
				bg1->GetRenderer()->SetFixSize(Vector(235, WIN_HIGHT));
				rollPattern = 1;
			}
			else if (rollPattern == 1)
			{
				static StaticMesh* splits[3] = {nullptr};
				AudioSource bgm("res/sounds/chooseyourseeds.mp3");
				player_->SetVolume(1000-num);
				num += 4;
				roll->SetPosition(Vector(num + 10, 240 + num / 29));
				rollCap->SetPosition(Vector(num + 8, 328 + num / 22));
				roll->GetRenderer()->SetScale(Vector(68 - num / 14, 141 - num / 26), "roll");
				rollCap->GetRenderer()->SetScale(Vector(73 - num / 14, 71 - num / 14), "rollCap");
				bg1->GetRenderer()->SetFixSize(Vector(num + 235, WIN_HIGHT));

				int index = num % 96 / 16;
				int delta = num > 500 ? num / 5 : 0;
				if (num == 4) {
					splits[0] = GameStatics::CreateObject<ASplit>(Vector(-35, 0));
					splits[0]->SetAttachment(roll);
				}
				else if (num == 20) {
					splits[1] = GameStatics::CreateObject<ASplit_>(Vector(-25,30));
					splits[1]->SetAttachment(roll);
				}
				else if (num == 36) {
					splits[2] = GameStatics::CreateObject<ASplit>(Vector(-30, 70));
					splits[2]->SetAttachment(roll);
				}
				for (int i = 0; i < 3; i++) {
					if (splits[i]) splits[i]->GetRenderer()->SetTransparency(255 - index * 20 - delta);
				}

				if (num >= 800) { 
					bAniFlag = false; 
					AudioSource bgm1("res/sounds/roll.mp3");
					player->Close(bgm1);
					roll->Destroy(); rollCap->Destroy(); bg0->Destroy();
				}
			}
		}
		return;
	}

	float time = MainControlTimeHandle.GetDelay();
	if (time >= 75 && time<100)//三行
	{
		static StaticMesh* roll = nullptr;
		static StaticMesh* rollCap = nullptr;
		static StaticMesh* roll_ = nullptr;
		static StaticMesh* rollCap_ = nullptr;
		static int num = 0;
		if (rollPattern == 1) {
			AudioSource bgm("res/sounds/roll.mp3");
			player->Play(bgm, true);
			rollPattern = 2;
			roll = GameStatics::CreateObject<StaticMesh>(Vector(10, 142));
			roll->GetRenderer()->Load("roll");
			roll->GetRenderer()->SetLayer(1);
			rollCap = GameStatics::CreateObject<StaticMesh>(Vector(8, 230));
			rollCap->GetRenderer()->Load("rollCap");
			rollCap->GetRenderer()->SetLayer(2);
			roll_ = GameStatics::CreateObject<StaticMesh>(Vector(10, 342));
			roll_->GetRenderer()->Load("roll");
			roll_->GetRenderer()->SetLayer(5);
			rollCap_ = GameStatics::CreateObject<StaticMesh>(Vector(8, 430));
			rollCap_->GetRenderer()->Load("rollCap");
			rollCap_->GetRenderer()->SetLayer(6);
			bg3 = GameStatics::CreateObject<StaticMesh>(Vector(-225, 0));
			bg3->GetRenderer()->Load("bg3");
			bg3->GetRenderer()->SetLayer(-6);
			bg3->GetRenderer()->SetFixSize(Vector(235, WIN_HIGHT));
		}
		else if (rollPattern == 2)
		{
			static StaticMesh* splits[6] = { nullptr };
			num += 4;
			roll->SetPosition(Vector(num + 10, 142 + num / 29));
			rollCap->SetPosition(Vector(num + 8, 230 + num / 22));
			roll->GetRenderer()->SetScale(Vector(68 - num / 14, 141 - num / 26), "roll");
			rollCap->GetRenderer()->SetScale(Vector(73 - num / 14, 71 - num / 14), "rollCap");
			roll_->SetPosition(Vector(num + 10, 342 + num / 29));
			rollCap_->SetPosition(Vector(num + 8, 430 + num / 22));
			roll_->GetRenderer()->SetScale(Vector(68 - num / 14, 141 - num / 26), "roll");
			rollCap_->GetRenderer()->SetScale(Vector(73 - num / 14, 71 - num / 14), "rollCap");
			bg3->GetRenderer()->SetFixSize(Vector(num + 235, WIN_HIGHT));

			int index = num % 96 / 16;
			int delta = num > 500 ? num / 5 : 0;
			if (num == 4) {
				splits[0] = GameStatics::CreateObject<ASplit>(Vector(-35, 0)); splits[0]->SetAttachment(roll);
				splits[3] = GameStatics::CreateObject<ASplit>(Vector(-35, 0)); splits[3]->SetAttachment(roll_);
			}
			else if (num == 20) {
				splits[1] = GameStatics::CreateObject<ASplit_>(Vector(-25, 30)); splits[1]->SetAttachment(roll);
				splits[4] = GameStatics::CreateObject<ASplit>(Vector(-35, 0)); splits[4]->SetAttachment(roll_);
			}
			else if (num == 36) {
				splits[2] = GameStatics::CreateObject<ASplit>(Vector(-30, 70));splits[2]->SetAttachment(roll);
				splits[5] = GameStatics::CreateObject<ASplit>(Vector(-35, 0)); splits[5]->SetAttachment(roll_);
			}
			for (int i = 0; i < 6; i++)
				if (splits[i])splits[i]->GetRenderer()->SetTransparency(255 - index * 20 - delta);


			if (num >= 800) {
				AudioSource bgm1("res/sounds/roll.mp3");
				player->Close(bgm1);
				roll->Destroy(); rollCap->Destroy(); roll_->Destroy(); rollCap_->Destroy();
				bg1->Destroy(); rollPattern = 3;
			}
		}
	}
	else if (time >= 150)//五行
	{
		static StaticMesh* bg5 = nullptr;
		static StaticMesh* roll = nullptr;
		static StaticMesh* rollCap = nullptr;
		static StaticMesh* roll_ = nullptr;
		static StaticMesh* rollCap_ = nullptr; 
		static int num = 0;
		if (rollPattern == 3) {
			AudioSource bgm("res/sounds/roll.mp3");
			player->Play(bgm, true);
			rollPattern = 4;
			roll = GameStatics::CreateObject<StaticMesh>(Vector(10, 142));
			roll->GetRenderer()->Load("roll");
			roll->GetRenderer()->SetLayer(0);
			rollCap = GameStatics::CreateObject<StaticMesh>(Vector(8, 230));
			rollCap->GetRenderer()->Load("rollCap");
			rollCap->GetRenderer()->SetLayer(1);
			roll_ = GameStatics::CreateObject<StaticMesh>(Vector(10, 342));
			roll_->GetRenderer()->Load("roll");
			roll_->GetRenderer()->SetLayer(6);
			rollCap_ = GameStatics::CreateObject<StaticMesh>(Vector(8, 430));
			rollCap_->GetRenderer()->Load("rollCap");
			rollCap_->GetRenderer()->SetLayer(7);
			bg5 = GameStatics::CreateObject<StaticMesh>(Vector(-225, 0));
			bg5->GetRenderer()->Load("bg5");
			bg5->GetRenderer()->SetLayer(-5);
			bg5->GetRenderer()->SetFixSize(Vector(235, WIN_HIGHT));
		}
		else if (rollPattern == 4)
		{
			static StaticMesh* splits[6] = { nullptr };
			num += 4;
			roll->SetPosition(Vector(num + 10, 42 + num / 29));
			rollCap->SetPosition(Vector(num + 8, 130 + num / 22));
			roll->GetRenderer()->SetScale(Vector(68 - num / 14, 141 - num / 26), "roll");
			rollCap->GetRenderer()->SetScale(Vector(73 - num / 14, 71 - num / 14), "rollCap");
			roll_->SetPosition(Vector(num + 10, 442 + num / 29));
			rollCap_->SetPosition(Vector(num + 8, 530 + num / 22));
			roll_->GetRenderer()->SetScale(Vector(68 - num / 14, 141 - num / 26), "roll");
			rollCap_->GetRenderer()->SetScale(Vector(73 - num / 14, 71 - num / 14), "rollCap");
			bg5->GetRenderer()->SetFixSize(Vector(num + 235, WIN_HIGHT));

			int index = num % 96 / 16;
			int delta = num > 500 ? num / 5 : 0;
			if (num == 4) {
				splits[0] = GameStatics::CreateObject<ASplit>(Vector(-35, 0)); splits[0]->SetAttachment(roll);
				splits[3] = GameStatics::CreateObject<ASplit>(Vector(-35, 0)); splits[3]->SetAttachment(roll_);
			}
			else if (num == 20) {
				splits[1] = GameStatics::CreateObject<ASplit_>(Vector(-25, 30)); splits[1]->SetAttachment(roll);
				splits[4] = GameStatics::CreateObject<ASplit>(Vector(-35, 0)); splits[4]->SetAttachment(roll_);
			}
			else if (num == 36) {
				splits[2] = GameStatics::CreateObject<ASplit>(Vector(-30, 70)); splits[2]->SetAttachment(roll);
				splits[5] = GameStatics::CreateObject<ASplit>(Vector(-35, 0)); splits[5]->SetAttachment(roll_);
			}
			for (int i = 0; i < 6; i++)
				if (splits[i])splits[i]->GetRenderer()->SetTransparency(255 - index * 20 - delta);

			if (num >= 800) {
				AudioSource bgm1("res/sounds/roll.mp3");
				player->Close(bgm1);
				roll->Destroy(); rollCap->Destroy(); roll_->Destroy(); rollCap_->Destroy();
				bg3->Destroy(); rollPattern = 5;
			}
		}
	}


	/* 参数及生成控制 */

	//开场UI及音乐

	static bool flag = true;
	if (time < 1)
	{
		static int num = 200;
		player_->SetVolume(num-=2);

		
		if(ui->SeedBank->GetAbsoluteLocation().y<0)ui->SeedBank->AddLocation(Vector(0,4));

		static DWORD lasForCar = timeGetTime();
		static int numForCar = 4;
		if (timeGetTime() - lasForCar >= 75 && numForCar>=0) {
			ACar* buf = GameStatics::CreateObject<ACar>(Vector(-75, 125+100*numForCar--));
			buf->GetRenderer()->SetLayer(numForCar + 1);
			lasForCar = timeGetTime();
		}
	}
	else if (time >= 1 && time < 1.75) {
		ui->StartTitle0->SetVisibility(true); 
		if (flag) {
			AudioSource bgm("res/sounds/chooseyourseeds.mp3");
			player_->Close(bgm);
			player_->Destruct();

			AudioSource bgm1("res/sounds/start.mp3");
			AudioSource bgm2("res/sounds/pioneer.mp3");
			player->Play(bgm1);
			player->Play(bgm2, true);
			flag = false;
		}
	}
	else if (time >= 1.75 && time < 2.5){
		ui->StartTitle1->SetVisibility(true);	ui->StartTitle0->SetVisibility(false);
	}
	else if(time >= 2.5 && time < 3.25){
		ui->StartTitle2->SetVisibility(true); ui->StartTitle1->SetVisibility(false);
	}
	else {
		ui->StartTitle2->SetVisibility(false);
		ui->Scoop->SetVisibility(true);
		ui->Blank->SetVisibility(true);
		ui->bStart = true;
	}
	


	//银行数字闪烁
	if (BlinkTimeHandle.GetDelay() < 0.75f && 
		(int(BlinkTimeHandle.GetDelay()*1000))%100<50)
		ui->sunNum = string("$9") + to_string(sunShine);
	else ui->sunNum = to_string(sunShine);

	if (ui->failFlag) {
		AudioSource bgm("res/sounds/cursor/failcardhit.mp3");
		player->Play(bgm);
		if (ui->failFlag == 2)
		BlinkTimeHandle.ReSet();
		ui->failFlag = 0;
	}


	//天空阳光生成
	SunTimeHandle.Tick();

	
	/* 植物 */
	if (msg.lbutton)
	{
		if (ui->index >= 0 && curIndex != ui->index)
		{
			if (plant)plant->Destroy();
			curIndex = ui->index;

			switch (curIndex)
			{
			case 0:plant = GameStatics::CreateObject<APeaShooter>(GetCursorWorldPosition());
				break;
			case 1:plant = GameStatics::CreateObject<ASunFlower>(GetCursorWorldPosition());
				break;
			case 2:plant = GameStatics::CreateObject<ACherryBomb>(GetCursorWorldPosition());
				break;
			case 3:plant = GameStatics::CreateObject<AWallNut>(GetCursorWorldPosition());
				break;
			case 4:plant = GameStatics::CreateObject<AMine>(GetCursorWorldPosition());
				break;
			case 5:plant = GameStatics::CreateObject<AIceShooter>(GetCursorWorldPosition());
				break;
			case 6:plant = GameStatics::CreateObject<AChomper>(GetCursorWorldPosition());
				break;
			case 7:plant = GameStatics::CreateObject<ADoubleShooter>(GetCursorWorldPosition());
				break;
			}
			if(plant)
			plant->GetRenderer()->SetLayer(10);

			AudioSource bgm("res/sounds/cursor/cardhit.mp3");
			player->Play(bgm);
		}//创建植物

		if (plant && ui->index < 0) {
			Pair coor = FindCoordinate(GetCursorWorldPosition());
			int j = 0;
			if (rollPattern >= 3 && rollPattern < 5)j = 1;
			else if (rollPattern >= 5)j = 2;
			if (coor.x >= 0 && coor.x < 9 && coor.y >= 2-j && coor.y <= 2+j)
			{
				if (!plants[coor.x][coor.y]) {
					plant->SetPosition(Vector(coor.x * 80 + 30, coor.y * 100 + 90));
					plant->Enabled(true);
					plant->column = coor.x, plant->row = coor.y;
					sunShine -= plant->GetPrice();
					plants[coor.x][coor.y] = plant;
					ui->timers[curIndex].ReSet();
					GameStatics::CreateObject<AGrow>(plant->GetWorldPosition() + Vector(0, 45));
					plant = nullptr, curIndex = -1;
					AudioSource bgm("res/sounds/cursor/plant.mp3");
					player->Play(bgm);
				}
			}
			else{
				plant->Destroy(); plant = nullptr,curIndex = -1;
			}
			

			if (prePlant)
			{
				prePlant->Destroy(); prePlant = nullptr;
			}
		}//固定植物
	}

	if (ui->index < 0 && curIndex>=0) {
		Pair coor = FindCoordinate(GetCursorWorldPosition());
		int j = 0;
		if (rollPattern >= 3 && rollPattern < 5)j = 1;
		else if (rollPattern >= 5)j = 2;
		if (coor.x >= 0 && coor.x < 9 && coor.y >= 2-j && coor.y <= 2+j && !plants[coor.x][coor.y])
		{
			if (!prePlant) {
				switch (curIndex)
				{
				case 0:prePlant = GameStatics::CreateObject<APeaShooter>(GetCursorWorldPosition());
					break;
				case 1:prePlant = GameStatics::CreateObject<ASunFlower>(GetCursorWorldPosition());
					break;
				case 2:prePlant = GameStatics::CreateObject<ACherryBomb>(GetCursorWorldPosition());
					break;
				case 3:prePlant = GameStatics::CreateObject<AWallNut>(GetCursorWorldPosition());
					break;
				case 4:prePlant = GameStatics::CreateObject<AMine>(GetCursorWorldPosition());
					break;
				case 5:prePlant = GameStatics::CreateObject<AIceShooter>(GetCursorWorldPosition());
					break;
				case 6:prePlant = GameStatics::CreateObject<AChomper>(GetCursorWorldPosition());
					break;
				case 7:prePlant = GameStatics::CreateObject<ADoubleShooter>(GetCursorWorldPosition());
					break;
				}
				if (prePlant) {
					prePlant->GetRenderer()->SetLayer(0);
					prePlant->GetRenderer()->SetTransparency(100);
				}
			}
		}
		else {
			if(prePlant)prePlant->Destroy();
			prePlant = nullptr;
		}
	}//管理虚拟植物


	if (plant)
	{
		plant->SetPosition(GetCursorWorldPosition()-Vector(40,40));
	}
	if (prePlant)
	{
		Pair coor = FindCoordinate(GetCursorWorldPosition());
		int j = 0;
		if (rollPattern >= 3 && rollPattern < 5)j = 1;
		else if (rollPattern >= 5)j = 2;
		if (coor.x >= 0 && coor.x < 9 && coor.y >= 2-j && coor.y <= 2+j) 
		prePlant->SetPosition(Vector(coor.x * 80 + 30, coor.y * 100 + 90));
	}

	/* 铲子 */

	if (plantUnderScoop && *plantUnderScoop){
		(*plantUnderScoop)->GetRenderer()->SetTransparency(255);
		plantUnderScoop = nullptr;
	}//铲子所在植物高亮恢复

	if (ui->scoopFlag)
	{
		ui->Scoop->SetLocation(GetCursorWorldPosition() - Vector(25, 25));

		Pair coor = FindCoordinate(GetCursorWorldPosition());
		if (coor.x >= 0 && coor.x < 9 && coor.y >= 0 && coor.y < 5) {
			if (plants[coor.x][coor.y])
			{
				plantUnderScoop = &plants[coor.x][coor.y];
				plants[coor.x][coor.y]->GetRenderer()->SetTransparency(180);
			}
		}

		if (msg.lbutton) {
			if (coor.x >= 0 && coor.x < 9 && coor.y >= 0 && coor.y < 5) {
				if (plants[coor.x][coor.y])
				{
					plants[coor.x][coor.y]->Destroy();
					plants[coor.x][coor.y] = nullptr;
				}
				AudioSource bgm("res/sounds/cursor/plant.mp3");
				player->Play(bgm);
			}
			ui->scoopFlag = false;
			ui->Scoop->SetLayer(-1);
			ui->Scoop->SetLocation(Vector(536, 0));
		}
	}
	if (ui->Blank->IsCursorOn() && msg.lbutton) {
		ui->scoopFlag = true; ui->Scoop->SetLayer(20);
		AudioSource bgm("res/sounds/cursor/scoopsound.mp3");
		player->Play(bgm);
	}



	/* 僵尸 */

	//僵尸生成
	if (MainControlTimeHandle.GetDelay() > generateTime[zombieNum] && zombieNum<80) Generate(); 
	else if (zombieNum >= 80)BossGenerateTimeHandle.Tick();


	if (zombieNum == 80) {
		boss = GameStatics::CreateObject<ABossZombie>(Vector(650, 245));
		boss->row = 2;
		boss->GetRenderer()->SetLayer(4);
		zombieNumPerRow[2]++;

		AudioSource bgm1("res/sounds/elite.mp3");
		player->Close(bgm1);

		AudioSource bgm2("res/sounds/boss.mp3");
		player->Play(bgm2, true);
		zombieNum++;


		ui->Blood->SetVisibility(true);
		ui->Blood_1->SetVisibility(true);
	}
	if (boss && boss->GetBlood()>0) { ui->Blood_1->SetPicSize(Vector(412.f * boss->GetBlood()/1000, 24)); }
	//Boss
}


void ABattleController::Produce()
{
	int x = RandEx(100,700);
	ASun* buf = GameStatics::CreateObject<ASun>(Vector(x, 0));
	buf->line = RandEx(200, 500);
	buf->rigid->EnableGravity(false);
	buf->rigid->SetVelocity(Vector(0,0.6));
}

void ABattleController::Generate()
{
	if (comeFlag) {
		AudioSource bgm("res/sounds/zombieCome.mp3");
		player->Play(bgm);
		comeFlag = false;

		ui->Level->SetVisibility(true);
		ui->EmptyBar->SetVisibility(true);
		ui->FullBar->SetVisibility(true);
		ui->Head->SetVisibility(true);

		for (int i = 0; i < 3; i++)ui->Flag[i]->SetVisibility(true);
	}
	//僵尸首次出现

	zombieNum++;
	{
		if (zombieNum == 13) {
			AudioSource bgm("res/sounds/warnings/warning.mp3");
			player->Play(bgm);
			ui->Warning->SetVisibility(true); return;
		}
		else if (zombieNum == 14)
		{
			AudioSource bgm("res/sounds/warnings/bigcoming.mp3");
			player->Play(bgm);
			ui->Warning->SetVisibility(false);
			ui->Flag[0]->SetLocation(ui->Flag[0]->GetAbsoluteLocation() + Vector(0, -10));
		}
		else if (zombieNum == 21) {
			AudioSource bgm("res/sounds/pioneer.mp3");
			player->Close(bgm);

			AudioSource bgm1("res/sounds/elite.mp3");
			player->Play(bgm1, true);
		}
		else if (zombieNum == 45) {
			AudioSource bgm("res/sounds/warnings/warning.mp3");
			player->Play(bgm);
			ui->Warning->SetVisibility(true); return;
		}
		else if (zombieNum == 46) {
			AudioSource bgm("res/sounds/warnings/bigcoming.mp3");
			player->Play(bgm);
			ui->Warning->SetVisibility(false);
			ui->Flag[1]->SetLocation(ui->Flag[1]->GetAbsoluteLocation() + Vector(0, -10));
		}
		else if (zombieNum == 61) {
			AudioSource bgm("res/sounds/warnings/warning.mp3");
			player->Play(bgm);
			ui->Warning->SetVisibility(true); return;
		}
		else if (zombieNum == 62) { ui->Warning->SetVisibility(false); return; }
		else if (zombieNum == 63) {
			AudioSource bgm("res/sounds/warnings/bigcoming.mp3");
			AudioSource bgm1("res/sounds/warnings/finalwarning.mp3");
			player->Play(bgm);
			player->Play(bgm1);
			ui->FinalWarning->SetVisibility(true);
			ui->Flag[2]->SetLocation(ui->Flag[2]->GetAbsoluteLocation() + Vector(0, -10));
		}
		else if (zombieNum == 64)ui->FinalWarning->SetVisibility(false);
	}
	//主要事件


	int length = zombieNum * 2+10;
	if (length > 157)length = 157;
	ui->FullBar->SetPicSize(Vector(length,21));
    ui->FullBar->SetPicLoc(Vector(ui->FullBar->GetSize().x - length, 0));
	ui->FullBar->SetLocation(Vector(732-length,575));
	ui->Head->SetLocation(ui->FullBar->GetAbsoluteLocation());
	//僵尸进度条更新记录

	
	int i = 2;
	if (rollPattern >= 3 && rollPattern < 5)
		i = RandEx(1, 3);
	else if (rollPattern >= 5)
		i = RandEx(0, 4);
	AZombie* buf;
	if (zombieNum < 10)
		buf = GameStatics::CreateObject<ANormalZombie>(Vector(800, i * 100 + 45));
	else if (zombieNum < 25)
	{
		int number = RandEx(0, 4);
		if (number < 3)buf = GameStatics::CreateObject<ANormalZombie>(Vector(800, i * 100 + 45));
		else buf = GameStatics::CreateObject<AHatZombie>(Vector(800, i * 100 + 45));
	}
	else if(zombieNum < 50) {
		int number = RandEx(0, 11);
	    if(number < 3)buf = GameStatics::CreateObject<ANormalZombie>(Vector(800, i * 100 + 45));
		else if (number < 6)buf = GameStatics::CreateObject<AHatZombie>(Vector(800, i * 100 + 45));
		else if(number < 9)buf = GameStatics::CreateObject<ABucketZombie>(Vector(800, i * 100 + 45));
		else buf = GameStatics::CreateObject<AJumpZombie>(Vector(800, i * 100 + 45));
	}
	else
	{
		int number = RandEx(0, 14);
		if (number < 3)buf = GameStatics::CreateObject<ANormalZombie>(Vector(800, i * 100 + 45));
		else if (number < 6)buf = GameStatics::CreateObject<AHatZombie>(Vector(800, i * 100 + 45));
		else if (number < 9)buf = GameStatics::CreateObject<ABucketZombie>(Vector(800, i * 100 + 45));
		else if (number < 12)buf = GameStatics::CreateObject<AJumpZombie>(Vector(800, i * 100 + 45));
		else buf = GameStatics::CreateObject<AArmorZombie>(Vector(800, i * 100 + 45));
	}
	buf->row = i;
	buf->GetRenderer()->SetLayer(i+2);
	zombieNumPerRow[i]++;
	//僵尸生成


	AudioSource bgm;
	int num = RandEx(0, 10);
	switch (num)
	{
	case 0: bgm.Load("res/sounds/zombieGenerate/hello.mp3"); break;
	case 1: bgm.Load("res/sounds/zombieGenerate/hello_1.mp3"); break;
	case 2: bgm.Load("res/sounds/zombieGenerate/hello_2.mp3"); break;
	case 3: bgm.Load("res/sounds/zombieGenerate/hello_3.mp3"); break;
	}
	if(num<4)
	player->Play(bgm);
	//随机播放僵尸出现音效
}

void ABattleController::Generate_()
{
	zombieNum++;	
	int i = RandEx(0, 4);
	AZombie* buf;
	int number = RandEx(0, 14);
	if (number < 3)buf = GameStatics::CreateObject<ANormalZombie>(Vector(800, i * 100 + 45));
	else if (number < 6)buf = GameStatics::CreateObject<AHatZombie>(Vector(800, i * 100 + 45));
	else if (number < 9)buf = GameStatics::CreateObject<ABucketZombie>(Vector(800, i * 100 + 45));
	else if (number < 12)buf = GameStatics::CreateObject<AJumpZombie>(Vector(800, i * 100 + 45));
	else buf = GameStatics::CreateObject<AArmorZombie>(Vector(800, i * 100 + 45));
	buf->row = i;
	buf->GetRenderer()->SetLayer(i + 2);
	zombieNumPerRow[i]++;
	//僵尸生成


	AudioSource bgm;
	int num = RandEx(0, 10);
	switch (num)
	{
	case 0: bgm.Load("res/sounds/zombieGenerate/hello.mp3"); break;
	case 1: bgm.Load("res/sounds/zombieGenerate/hello_1.mp3"); break;
	case 2: bgm.Load("res/sounds/zombieGenerate/hello_2.mp3"); break;
	case 3: bgm.Load("res/sounds/zombieGenerate/hello_3.mp3"); break;
	}
	if (num < 4)player->Play(bgm);
	//随机播放僵尸出现音效
}
 


