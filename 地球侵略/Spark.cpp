#include "Spark.h"



Spark::Spark()
{
}

Spark::Spark(int x, int y, int img) {
	this->x = x;
	this->y = y;
	this->imgSpark = img;
	this->id = ObjectID::spark;
	collision = new Collision(0, 0, 32, 64);
	LoadDivGraph("data/img/biribiri2.png", 4, 4, 1, 32, 64, biribiriHandle);
}

int Spark::update(const Collision & playerCol) {
	collision->updatePos(x, y);
	collisionCheck(playerCol);
	return 0;
}

void Spark::Draw(int drawX, int drawY) {
	//DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);

	DrawGraph(x - drawX, y - drawY, biribiriHandle[frame/6%4], true);
	frame++;
	if (frame > 60 ) frame = 0;
}

void Spark::collisionCheck(const Collision & target) {
	//プレイヤー側での処理に変更
}

Spark::~Spark()
{
}
