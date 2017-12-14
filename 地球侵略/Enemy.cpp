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

Enemy::Enemy(int x, int y, int img, int id, iHitAction * hit){
	this->x = x;
	this->y = y;
	this->imgHundle = img;
	this->enemyID = id;
	LoadDivGraph("data/img/enemy1Walk.png", 8, 4, 2, 64, 64, walk);
	HitAction = hit;
}

void Enemy::Update()
{
	MoveCommon();
}

void Enemy::Draw(int drawX, int drawY) 
{
	DrawFormatString(0,0,0xFFFFFF,"Enemy:%d,%d     Draw:%d,%d",x,y, x - drawX, y - drawY);
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

int Enemy::hitCheck(Object* target){
	//Object‚©‚çŽ‚Á‚Ä‚«‚½
	const int size = 64;
	float tMargin = (1 - target->collisionSize) / 2;
	tMargin = 0;
	float mMargin = (1 - collisionSize) / 2;
	mMargin = 0;
	int tX1 = target->x*(1 + tMargin);
	int tX2 = target->x + size* target->collisionSize;
	int tY1 = target->y*(1 + tMargin);
	int tY2 = target->y + size* target->collisionSize;

	int mX1 = x*(1 + mMargin);
	int mX2 = x + size* collisionSize;
	int mY1 = y*(1 + mMargin);
	int mY2 = y + size* collisionSize;


	if ((tX1 < mX2) && (tX2 > mX1) &&
		(tY1 < mY2) && (tY2 > mY1)) {
		/*“–‚½‚Á‚Ä‚¢‚½ê‡‚ÉŽÀs*/
		//onHit(target);

		HitAction->doHitAction(0);
		return 1;
	}
	else {
		return 0;

	}




	//if (Object::hitCheck(target)) {
	//	HitAction->doHitAction(0);
	//	DrawBox(600,600, 32, 64, 0xFF0000, true);
	//}

	//Object::hitCheck(target);
	return 0;
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

