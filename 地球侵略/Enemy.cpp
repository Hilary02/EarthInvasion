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
	LoadDivGraph("data/img/enemy1Atack.png", 4, 4, 1, 64, 64, atackHundle);
	collision = new Collision(colXOffset, colYOffset, colXSize, colYSize);
//	AttackBox = new Collision(atackRen, colYOffset, 320, colYSize);
	AttackBox = new Collision(32, colYOffset, -160, colYSize);

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

void Enemy::Update(const Collision & playerCol)
{
	collision->updatePos(x, y);
	AttackBox->updatePos(x, y);
	collisionCheck(playerCol);
}

void Enemy::Draw(int drawX, int drawY)
{
	DrawBox(AttackBox->hitRange.xPos + AttackBox->hitRange.xOffset -drawX, AttackBox->hitRange.yPos + AttackBox->hitRange.yOffset - drawY, AttackBox->hitRange.xPos + AttackBox->hitRange.xOffset - drawX+AttackBox->hitRange.xSize, AttackBox->hitRange.yPos + AttackBox->hitRange.yOffset - drawY+AttackBox->hitRange.ySize, 0x00FF00, false);


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
	int attackR = AttackBox->doCollisonCheck((target.hitRange));
	if (isCol) {
		movedis = 0;
		DrawBox(10, 20, 100, 200, 0xFF0000, true);
		IcolMgr->requestAction(Action::DmgPlayer);
	}
	else if(attackR){
		DrawBox(10,20,100,200, 0x0000ff,true);
		AtackCommon();
	}
	else {
		DrawBox(10, 20, 100, 200, 0xFF0000, false);
		MoveCommon();
	}
}

void Enemy::MoveCommon()
{
	movedis = 1;
	if (isRight)
	{
		x += movedis;
	}
	else
	{
		x -= movedis;
	}
	imgHandle = walk[(drawcount / 8) % 8];
	drawcount++;
	
	//countƒŠƒZƒbƒgŒã‰ñ‚µ
	//if (drawcount == 72) drawcount = 0;
}

void Enemy::AtackCommon()
{
	movedis = 0;
	imgHandle = atackHundle[(drawcount / 12) % 4];
	drawcount++;
}

bool Enemy::IsRangeCheck()
{
	dis += movedis;
	if (moveRange < dis)
	{
		dis = 0;
		AttackBox->flip();
		return !isRight;
	}
	else
	{
		return isRight;
	}
}

