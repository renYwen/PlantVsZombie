#include "BaseBullet.h"
#include"GameStatics.h"
#include"BoxCollider.h"



ABullet::ABullet()
{
	box = GameStatics::ConstructComponent<BoxCollider>(Vector(0, 0));
	box->SetAttachment(root);
	box->SetType("Bullet");
}
