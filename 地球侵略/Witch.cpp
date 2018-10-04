#include "Witch.h"



Witch::Witch(int x, int y, int img, IObjectManager* Iobj)
{
	this->IobjMgr = Iobj;
	this->x = x;
	this->y = y;
	this->imgHandle = img;
	this->id = id;

	IobjMgr->witchMoveRangeCalc(x, y, &minX, &maxX);
	
	setHp(5);
	setAtk(5);

	LoadDivGraph("data/img/enemy2Walk.png", 4, 4, 1, 64, 64, moveHandle);
	LoadDivGraph("data/img/enemy2WaitForAtack.png", 4, 4, 1, 64, 64, atackHandle);
	LoadDivGraph("data/img/enemy2Atack.png", 4, 4, 1, 64, 64, &atackHandle[4]);
	LoadDivGraph("data/img/enemy2Die.png", 8, 4, 2, 64, 64, deadHandle);
	damegeHandle = LoadGraph("data/img/enemy2Damage.png");
	bulletHandle = LoadGraph("data/img/bullet2.png");

	collision = new Collision(16, 0, 32, 64);
	AttackBox = new Collision(30, 0, -300, 256);
	state = State::alive;
}


Witch::~Witch()
{
}

void Witch::Draw(int drawX, int drawY)
{
	DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);
	DrawBox(AttackBox->hitRange.xPos + AttackBox->hitRange.xOffset - drawX, AttackBox->hitRange.yPos + AttackBox->hitRange.yOffset - drawY, AttackBox->hitRange.xPos + AttackBox->hitRange.xOffset - drawX + AttackBox->hitRange.xSize, AttackBox->hitRange.yPos + AttackBox->hitRange.yOffset - drawY + AttackBox->hitRange.ySize, 0x00FF00, false);
	if (isRight)
	{
		DrawTurnGraph(x - drawX, y - drawY, imgHandle, true);
	}
	else
	{
		DrawGraph(x - drawX, y - drawY, imgHandle, true);
	}

}

void Witch::attack()
{

}

void Witch::Floating()
{
	if (!isMove && state == State::alive)
	{
		drawcount = 0;
		isMove = true;
		isAtacck = false;
	}

	//movedis = movespeed;
	movedis = 1;
	if (state == State::dead)movedis = 0;

	if (isRight)
	{
		x += movedis;
	}
	else
	{
		x -= movedis;
	}
	imgHandle = moveHandle[(drawcount / 8) % 4];
	if (state == State::alive) drawcount += addCount;

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
	Enemy::DeadCheck();
	if (state == State::alive)
	{
		isRight = IsRangeCheck();
		collision->updatePos(x, y);
		AttackBox->updatePos(x, y);
		Floating();
	}
	return 0;
}

