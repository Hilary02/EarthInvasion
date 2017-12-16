#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Enemy::Enemy(int x, int y, int img, int id, ICollisionManager* IcolMgr){
	this->x = x;
	this->y = y;
	this->imgHandle = img;
	this->enemyID = id;
	LoadDivGraph("data/img/enemy1Walk.png", 8, 4, 2, 64, 64, walk);
	collision = new Collision(colXOffset, colYOffset, colXSize, colYSize);
	this->IcolMgr = IcolMgr;
}

//Enemy::Enemy(int x, int y, int img, int id,) {
//	this->x = x;
//	this->y = y;
//	this->imgHandle = img;
//	this->enemyID = id;
//	LoadDivGraph("data/img/enemy1Walk.png", 8, 4, 2, 64, 64, walk);
//	HitAction = hit;
//}

void Enemy::Update(Collision playerCol)
{
	MoveCommon();
	collision->updatePos(x, y);
	collisionCheck(playerCol);
}

void Enemy::Draw(int drawX, int drawY)
{
	DrawFormatString(0, 0, 0xFFFFFF, "Enemy:%d,%d     Draw:%d,%d", x, y, x - drawX, y - drawY);
	isRight = IsRangeCheck();
	if (isRight)
	{
		DrawTurnGraph(x - drawX, y - drawY, imgHandle, true);
	}
	else
	{
		DrawGraph(x - drawX, y - drawY, imgHandle, true);
	}
}

void Enemy::collisionCheck(const Collision & target) {
	int isCol = collision->doCollisonCheck((target.hitRange));
	if (isCol) {
		DrawBox(10, 20, 100, 200, 0xFF0000, true);
		IcolMgr->requestAction(Action::DmgPlayer);
	}
	else {
		DrawBox(10, 20, 100, 200, 0xFF0000, false);
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
	imgHandle = walk[(drawcount / 8) % 8];
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

