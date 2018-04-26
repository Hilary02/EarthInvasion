#include "Spark.h"



Spark::Spark()
{
}

Spark::Spark(int x, int y, int img) {
	this->x = x;
	this->y = y;
	this->imgSpark = img;
	this->id = ObjectID::spike;
	collision = new Collision(0, 0, 64, 256);
}

int Spark::update(const Collision & playerCol)
{
	collision->updatePos(x, y);
	collisionCheck(playerCol);

	return 0;
}

void Spark::Draw(int drawX, int drawY)
{
	DrawGraph(x - drawX, y - drawY, imgSpark, true);
}

void Spark::collisionCheck(const Collision & target) {
	//プレイヤー側での処理に変更
}

Spark::~Spark()
{
}
