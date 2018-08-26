#include "Witch.h"



Witch::Witch(int x, int y, int img, IObjectManager* Iobj)
{
	this->IobjMgr = Iobj;
	this->x = x;
	this->y = y;
	this->imgHandle = img;
	
	setHp(5);
	setAtk(5);

	LoadDivGraph("data/img/enemy2Walk.png", 8, 4, 2, 64, 64, moveHandle);
	LoadDivGraph("data/img/enemy2WaitForAtack.png", 4, 4, 1, 64, 64, atackHandle);
	LoadDivGraph("data/img/enemy2Atack.png", 4, 4, 1, 64, 64, &atackHandle[4]);
	LoadDivGraph("data/img/enemy2Die.png", 8, 4, 2, 64, 64, deadHandle);
	damegeHandle = LoadGraph("data/img/enemy2Damage.png");
	bulletHandle = LoadGraph("data/img/bullet2.png");

	collision = new Collision(16, 0, 20, 64);
}


Witch::~Witch()
{
}

void Witch::Draw(int drawX, int drawY)
{
	//DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);
	if (isRight)
	{
		DrawTurnGraph(x - drawX, y - drawY, imgHandle, true);
	}
	else
	{
		DrawGraph(x - drawX, y - drawY, imgHandle, true);
	}

}

void Witch::risingOrDescent()
{
	if (isUnder)
	{
		y--;
	}
	else
	{
		y++;
	}
}

int Witch::update(const Collision & playerCol)
{
	return 0;
}

