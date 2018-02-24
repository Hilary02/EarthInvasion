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

	collision = new Collision(0, 0, 16, 16);
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
	this->id = 100 + id;

	collision = new Collision(0, 0, 16, 16);
}


Bullet::~Bullet()
{
}

bool Bullet::Update()
{
	collision->updatePos(x, y);

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
		//remit = 0;
		return false;
	}
	else
	{
		return true;
	}
	
	
}

void Bullet::Draw(int drawX, int drawY)
{
	DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);
	DrawGraph(x - drawX, y - drawY, imgHandle, true);
}

int Bullet::update(const Collision & playerCol)
{
	collision->updatePos(x, y);
	int isCol = collision->doCollisonCheck((playerCol.hitRange));
	if (isCol)
	{
		CT++;
		if (CT > 3)
		{
			return -1;
		}
		return 0;
	}
	else if (remit > 120)
	{
		remit = 0;
		return -1;
	}
	else
	{
		return 0;
	}
}

bool Bullet::collisionCheck(const Collision & target)
{
	int isCol = collision->doCollisonCheck((target.hitRange));
	if (isCol)
	{
		return true;
	}
	else
	{
		return false;
	}
}
