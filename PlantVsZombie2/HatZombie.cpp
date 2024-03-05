#include "HatZombie.h"

AHatZombie::AHatZombie()
{
	name = HatZombie;
	blood = 29;

	
	walk.Load("hatwalk", 21, 1, 21, { 0,-12 });
	walk.SetInterval(0.12f);
	eat.Load("hateat", 11, 1, 11, {-10,-12});
	eat.SetInterval(0.1f);
	die.Load("zombiedie", 10, 1, 10, Vector(-65, -12));
	die.SetInterval(0.1f);

	walk_1.Load("hatwalk_1", 21, 1, 21, { 0,-12 });
	walk_1.SetInterval(0.24f);
	eat_1.Load("hateat_1", 11, 1, 11, {-10,-12});
	eat_1.SetInterval(0.2f);
	die_1.Load("zombiedie_1", 10, 1, 10, Vector(-65, -12));
	die_1.SetInterval(0.2f);

	ani->Insert("walk", walk);
	ani->Insert("eat", eat);
	ani->Insert("die", die);
	ani->Insert("walk_1", walk_1);
	ani->Insert("eat_1", eat_1);
	ani->Insert("die_1", die_1);
	ani->SetNode("walk");
}
