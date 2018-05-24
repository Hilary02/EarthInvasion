#include "Fire.h"

Fire::Fire()
{
}

Fire::Fire(int x, int y, int img) {
	this->x = x;
	this->y = y;
	this->imgFire = img;
	this->id = ObjectID::fire;
	collision = new Collision(0, 0, 16, 32);
	LoadDivGraph("data/img/Fire.png", 4, 4, 1, 32, 32, fireHandle);
}

int Fire::update(const Collision & playerCol) {
	collision->updatePos(x, y);
	collisionCheck(playerCol);
	
	return 0;
}

void Fire::Draw(int drawX, int drawY) {	
	if (drawCount >= 60) {
		drawCount = 0;
	}
		DrawGraph(x - drawX, y - drawY, fireHandle[drawCount / 15], TRUE);
		drawCount++;
}

void Fire::collisionCheck(const Collision & target) {
}

Fire::~Fire() {}
