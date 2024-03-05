#include "BucketZombie.h"


ABucketZombie::ABucketZombie()
{
	name = BucketZombie;
	blood = 65;

	walk.Load("bucketwalk", 5, 10, 46, Vector(-3, -5));
	walk.SetInterval(0.06f);
	eat.Load("bucketeat", 4, 10, 39, Vector(-3, -5));
	eat.SetInterval(0.03f);
	die.Load("zombiedie", 10, 1, 10, Vector(-65, -12));
	die.SetInterval(0.1f);

	walk_1.Load("bucketwalk_1", 5, 10, 46, Vector(-3, -5));
	walk_1.SetInterval(0.12f);
	eat_1.Load("bucketeat_1", 4, 10, 39, Vector(-3, -5));
	eat_1.SetInterval(0.06f);
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
