#include "ArmorZombie.h"


AArmorZombie::AArmorZombie()
{
	name = ArmorZombie;
	blood = 80;
	speed *= 2;

	walk.Load("armorwalk", 11, 1, 11, {-30,-10});
	walk.SetInterval(0.1f);
	eat.Load("armoreat", 10, 1, 10, Vector(-25, 3));
	eat.SetInterval(0.1f);
	die.Load("armordie", 14, 1, 14, Vector(-50, -12));
	die.SetInterval(0.08f);

	walk_1.Load("armorwalk_1", 11, 1, 11, { -30,-10 });
	walk_1.SetInterval(0.2f);
	eat_1.Load("armoreat_1", 10, 1, 10, Vector(-25, 3));
	eat_1.SetInterval(0.2f);
	die_1.Load("armordie_1", 14, 1, 14, Vector(-50, -12));
	die_1.SetInterval(0.16f);

	ani->Insert("walk", walk);
	ani->Insert("eat", eat);
	ani->Insert("die", die);
	ani->Insert("walk_1", walk_1);
	ani->Insert("eat_1", eat_1);
	ani->Insert("die_1", die_1);
	ani->SetNode("walk");
}
