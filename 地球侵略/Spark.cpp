#include "Spark.h"

Spark::Spark() {}
Spark::~Spark() {}

Spark::Spark(int x, int y, int img) {
	this->x = x;
	this->y = y;
	this->imgSpark = img;
	this->id = ObjectID::spark;
	collision = new Collision(1, 0, 30, 64);
	LoadDivGraph("data/img/biribiri2.png", 4, 4, 1, 32, 64, biribiriHandle);
}

int Spark::update(const Collision & playerCol) {
	collision->updatePos(x, y);
	collisionCheck(playerCol);
	frame++;
	if (frame > 60) frame = 0;
	return 0;
}

void Spark::Draw(int drawX, int drawY) {
	DrawGraph(x - drawX, y - drawY, biribiriHandle[frame / 6 % 4], true);

}

void Spark::collisionCheck(const Collision & target) {}
