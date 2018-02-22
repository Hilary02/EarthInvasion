#include "Bullet.h"

Bullet::Bullet()
{
}

Bullet::Bullet(int x, int y , int Hundle, bool isRight)
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
	isR = isRight;
}

Bullet::Bullet(int x, int y, int Hundle, bool isRight, int id)
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
	isR = isRight;
	this->id = id;
}


Bullet::~Bullet()
{
}

bool Bullet::Update()
{
	if (isR) {
		x++;
	}
	else
	{
		x--;
	}
	remit++;
	if (remit > 120)
	{
		remit = 0;
		return false;
	}
	else
	{
		return true;
	}
}

void Bullet::Draw(int drawX, int drawY)
{
	DrawGraph(x - drawX, y - drawY, imgHandle, true);
}
