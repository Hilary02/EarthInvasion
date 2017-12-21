#include "Bullet.h"



Bullet::Bullet()
{
}

Bullet::Bullet(int x, int y , int Hundle, bool isRight, ICollisionManager * Icol)
{
	if (isRight)
	{
		this->x = x + 60;
	}
	else
	{
		this->x = x;
	}
	this->y = y + 30;
	this->imgHandle = Hundle;
	this->IcolMgr = Icol;
	isR = isRight;
}


Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (isR) {
		x++;
	}
	else
	{
		x--;
	}
	remit++;
}

void Bullet::Draw(int drawX, int drawY)
{
	DrawGraph(x - drawX, y - drawY, imgHandle, true);
}
