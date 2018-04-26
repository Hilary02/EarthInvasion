#include "Spark.h"



Spark::Spark()
{
}

Spark::Spark(int x, int y, int img) {
	this->x = x;
	this->y = y;
	this->imgSpark = img;
	this->id = ObjectID::spark;
	collision = new Collision(0, 0, 16, 64);
}

int Spark::update(const Collision & playerCol) {
	collision->updatePos(x, y);
	collisionCheck(playerCol);
	frame++;
	return 0;
}

void Spark::Draw(int drawX, int drawY) {
	bool isTurn = (frame / 10 % 2);
	DrawRotaGraph(x - drawX, y - drawY, 1.0f, 0, imgSpark, TRUE, isTurn);
}

void Spark::collisionCheck(const Collision & target) {
	//プレイヤー側での処理に変更
}

Spark::~Spark()
{
}
