#include "Enemy.h"
#include "DxLib.h"



Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Enemy::Enemy(int x, int y, int img, int id)
{
	this->x = x;
	this->y = y;
	this->imgHundle = img;
	this->enemyID = id;
	LoadDivGraph("data/img/enemy1Walk.png", 8, 4, 2, 64, 64, walk);
}

void Enemy::Update()
{
	MoveCommon();
}

void Enemy::Draw(int drawX, int drawY) 
{
	isRight = IsRangeCheck();
	if (isRight) 
	{
		DrawTurnGraph(x - drawX, y - drawY, imgHundle, true);
	}
	else
	{
		DrawGraph(x - drawX, y - drawY, imgHundle, true);
	}
	

}


void Enemy::MoveCommon()
{	
	if (isRight)
	{
		x += MOVE;
	}
	else
	{
		x -= MOVE;
	}
	imgHundle = walk[(drawcount/8) % 8];
	drawcount++;
}

bool Enemy::IsRangeCheck()
{
	dis += MOVE;
	if (moveRange < dis)
	{
		dis = 0;
		return !isRight;
	}
	else
	{
		return isRight;
	}
}

