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
}

void Enemy::Update()
{
	MoveCommon();
}

void Enemy::Draw(int x , int y){
	DrawGraph(x, y, imgHundle, true);
}

void Enemy::MoveCommon()
{
	x += moveRange;
}


