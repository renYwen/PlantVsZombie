#include "Resources.h"


extern Resources ResourcePool{};


Resources::Resources()
{
	/* 渲染 */

	//子弹
	Load("pea", "res/animations/bullets/pea.png", 28, 28);
	Load("icepea", "res/animations/bullets/icepea.png", 28, 28);
	Load("sun", "res/animations/bullets/sun.png", 483, 160);

	//特效
	Load("pea_1", "res/animations/bullets/pea_1.png", 52, 46);
	Load("icepea_1", "res/animations/bullets/icepea_1.png", 52, 46);
	Load("boom", "res/animations/bullets/boom.png", 131, 92);
	Load("explosion", "res/animations/bullets/explosion.png", 240, 227);
	Load("soil", "res/animations/effects/soil.png", 76, 170);
	Load("split", "res/animations/effects/split.png", 61, 192);
	Load("split_", "res/animations/effects/split.png", 70, 234);
	Load("head", "res/animations/zombies/head.png", 135, 2004);
	Load("head_1", "res/animations/zombies/head_1.png", 135, 2004);
	Load("ash", "res/animations/zombies/ash.png", 100, 2880);
	Load("zombieHand", "res/animations/effects/ZombieHand.png", 2310,330);

	//植物
	Load("cherrybomb", "res/animations/plants/cherrybomb.png", 484, 512);
	Load("doubleshooter", "res/animations/plants/doubleshooter.png", 483, 320);
	Load("iceshooter", "res/animations/plants/iceshooter.png", 71, 1065);
	Load("mine", "res/animations/plants/mine.png", 75, 440);
	Load("mine_1", "res/animations/plants/mine_1.png", 75, 55);
	Load("peashooter", "res/animations/plants/peashooter.png", 483, 320);
	Load("sunflower", "res/animations/plants/sunflower.png", 483, 320);
	Load("sunflower_1", "res/animations/plants/sunflower_1.png", 483, 320);
	Load("wallnut", "res/animations/plants/wallnut.png", 483, 480);
	Load("wallnut_1", "res/animations/plants/wallnut_1.png", 65, 803);
	Load("wallnut_2", "res/animations/plants/wallnut_2.png", 483, 480);
	Load("chomper", "res/animations/plants/chomper.png", 89, 1105);
	Load("chomper_1", "res/animations/plants/chomper_1.png", 125, 972);
	Load("chomper_2", "res/animations/plants/chomper_2.png", 72, 468);
	
	//僵尸
	Load("zombiedie", "res/animations/zombies/die.png", 166, 1440);
	Load("zombiedie_1", "res/animations/zombies/die_1.png", 166, 1440);

	Load("bossidle", "res/animations/zombies/boss/idle.png", 154, 2580);
	Load("bossattack", "res/animations/zombies/boss/attack.png", 154, 1760);
	Load("armorwalk", "res/animations/zombies/armor/walk.png", 139,1584);
	Load("armoreat", "res/animations/zombies/armor/eat.png", 118,1290);
	Load("armorwalk_1", "res/animations/zombies/armor/walk_1.png", 139, 1584);
	Load("armoreat_1", "res/animations/zombies/armor/eat_1.png", 118, 1290);
	Load("armordie", "res/animations/zombies/armor/die.png", 180,2142);
	Load("armordie_1", "res/animations/zombies/armor/die_1.png", 180, 2142);
	Load("bucketwalk", "res/animations/zombies/bucket/walk.png", 1000, 695);
	Load("bucketeat", "res/animations/zombies/bucket/eat.png", 1000, 556);
	Load("bucketwalk_1", "res/animations/zombies/bucket/walk_1.png", 1000, 695);
	Load("bucketeat_1", "res/animations/zombies/bucket/eat_1.png", 1000, 556);
	Load("normalstand", "res/animations/zombies/normal/stand.png", 166, 1584);
	Load("normalwalk", "res/animations/zombies/normal/walk.png", 1000, 695);
	Load("normaleat", "res/animations/zombies/normal/eat.png", 1000, 556);
	Load("normalwalk_1", "res/animations/zombies/normal/walk_1.png", 1000, 695);
	Load("normaleat_1", "res/animations/zombies/normal/eat_1.png", 1000, 556);
	Load("hatstand", "res/animations/zombies/hat/stand.png", 166, 1152);
	Load("hatwalk", "res/animations/zombies/hat/walk.png", 97, 3024);
	Load("hateat", "res/animations/zombies/hat/eat.png", 95, 1584);
	Load("hatwalk_1", "res/animations/zombies/hat/walk_1.png", 97, 3024);
	Load("hateat_1", "res/animations/zombies/hat/eat_1.png", 95, 1584);

	Load("jumprun", "res/animations/zombies/jump/run.png", 1616, 960);
	Load("jumprun_1", "res/animations/zombies/jump/run_1.png", 1616, 960);
	Load("jumpjump", "res/animations/zombies/jump/jump.png", 1800, 1782);
	Load("jumpjump_1", "res/animations/zombies/jump/jump_1.png", 1800, 1782);
	Load("jumpwalk", "res/animations/zombies/jump/walk.png", 900, 810);
	Load("jumpwalk_1", "res/animations/zombies/jump/walk_1.png", 900, 810);
	Load("jumpeat", "res/animations/zombies/jump/eat.png", 900, 486);
	Load("jumpeat_1", "res/animations/zombies/jump/eat_1.png", 900, 486);
	Load("jumpdie", "res/animations/zombies/jump/die.png", 162, 1764);
	Load("jumpdie_1", "res/animations/zombies/jump/die_1.png", 162, 1764);

	//其他
	Load("roll", "res/images/SodRoll.png", 68,141);
	Load("rollCap", "res/images/SodRollCap.png", 71, 73);
	Load("bg0", "res/images/bg0.jpg", 1400, 600);
	Load("bg1", "res/images/bg1.jpg", 1400, 600);
	Load("bg3", "res/images/bg3.jpg", 1400, 600);
	Load("bg5", "res/images/bg5.jpg", 1400, 600);
	Load("car", "res/images/car.png", 70, 57);
	Load("smallShadow", "res/images/shadow.png", 25, 13);
	Load("bigShadow", "res/images/shadow.png", 67, 32);
	

	/* 媒体 */
	/*DWORD dwError1 = mciSendString("open res/sounds/start.mp3 alias start", NULL, 0, NULL);
	if (dwError1 != 0) {
		char szError[256];
		mciGetErrorString(dwError1, szError, 256);
		printf("MCI error: %s\n", szError);
	}*/
	/*Load("start", "res/sounds/start.mp3");
	Load("pioneer", "res/sounds/pioneer.mp3");*/
}

Resources::~Resources()
{
	for (auto i = imageRes.begin(); i != imageRes.end(); ++i)
		delete (*i).second;
}

void Resources::Load(std::string name, std::string path, int wid, int hei)
{
	IMAGE* buf = new IMAGE;
	loadimage(buf, LPCTSTR(path.c_str()), wid, hei);
	imageRes.insert({name,buf});
	imagePath.insert({ name,path });
}

void Resources::Load(std::string name, std::string path)
{
	std::string file = std::string("open ") + path + std::string(" alias ") + name;
	mciSendString(file.c_str(), NULL, 0, NULL);
}

IMAGE* Resources::Fetch(std::string name)
{
   return (*imageRes.find(name)).second;
}

std::string Resources::FindPath(std::string name)
{
	return (*imagePath.find(name)).second;
}


