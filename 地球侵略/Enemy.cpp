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

void Enemy::Draw(int x , int y){
	DrawGraph(x, y, imgHundle, true);
}

void Enemy::MoveCommon()
{	
	x += moveRange;
	DrawGraph(x, y, walk[drawcount%8],true);
	drawcount++;
}


