#include "RobotEnemy.h"



RobotEnemy::RobotEnemy(int x, int y, int img, IObjectManager* Iobj){
	this->IobjMgr = Iobj;
	this->x = x;
	this->y = y;
	this->imgHandle = img;
	IobjMgr->enemyMoveRangeCalc(x, y, &minX, &maxX);
	setHp(3);
	setAtk(3);
	movespeed = 1;
	atkInterval = 104;
	LoadDivGraph("data/img/enemy4Walk.png", 8, 4, 2, 64, 64, walkHandle);
	LoadDivGraph("data/img/enemy4WaitForAtack.png", 4, 4, 1, 64, 64, atackHandle);
	LoadDivGraph("data/img/enemy4Atack.png", 4, 4, 1, 64, 64, &atackHandle[4]);
	LoadDivGraph("data/img/enemy4Die.png", 8, 4, 2, 64, 64, deadHandle);
	damegeHandle = LoadGraph("data/img/enemy4Damage.png");
	bulletHandle = LoadGraph("data/img/bullet.png");
	collision = new Collision(16, 0, 20, 64);
	AttackBox = new Collision(32, colYOffset, -160, colYSize);
}


RobotEnemy::~RobotEnemy(){}

int RobotEnemy::update(const Collision & playerCol)
{
	Enemy::update(playerCol);
	return 0;
}

void RobotEnemy::Draw(int drawX, int drawY){
	Enemy::Draw(drawX, drawY);
}

void RobotEnemy::collisionCheck(const Collision & target){
	Enemy::collisionCheck(target);
}

void RobotEnemy::MoveCommon(){
	Enemy::MoveCommon();
}

void RobotEnemy::AtackCommon(){
	Enemy::AtackCommon();
}	

void RobotEnemy::DeadCheck(){
	Enemy::DeadCheck();
}

bool RobotEnemy::IsRangeCheck()
{
	rightFlg = Enemy::IsRangeCheck();
	return rightFlg;
}

