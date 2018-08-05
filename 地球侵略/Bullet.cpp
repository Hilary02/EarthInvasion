#include "Bullet.h"
#include "SoundManager.h"

Bullet::Bullet()
{
}

Bullet::Bullet(int x, int y, int atk, int Hundle, bool isRight, ObjectID id)
{
	if (isRight) { this->x = x + 60; }
	else { this->x = x; }
	this->atk = atk;
	this->y = y + 30;
	this->imgHandle = Hundle;
	isR = isRight;
	this->id = id;

	collision = new Collision(0, 0, 16, 16);
	SoundM.Se("data/se/Hit.wav");
}


Bullet::~Bullet()
{
}

bool Bullet::isOutOfRange()
{
	if (remit > 120)
	{
		return false;
	}
	else
	{
		return true;
	}


}

void Bullet::Draw(int drawX, int drawY)
{
	//DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);
	DrawGraph(x - drawX, y - drawY, imgHandle, true);
}

int Bullet::update(const Collision & playerCol)
{
	//collision->updatePos(x, y);
	int isCol = collision->doCollisonCheck((playerCol.hitRange));
	collision->updatePos(x, y);

	if (isR) x += MOVEDIS;
	else { x -= MOVEDIS; }
	remit++;

	if (isCol)
	{
		//�e��HP�ɉe����^����O�ɏ���������,���̑Ώ�
		CT++;
		if (CT > 1)st = -1;
		return st;
	}
	else if (remit > 120)
	{
		remit = 0;
		st = -1;
		return st;
	}
	else
	{
		return st;
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

void Bullet::setState(int st)
{
	this->st = st;
}

int Bullet::getAtk()
{
	return atk;
}
