#include "DxLib.h"
#include "Abyss.h"

Abyss::Abyss() {}
Abyss::~Abyss() {}

Abyss::Abyss(int x, int y, int img) {
	this->x = x;
	this->y = y;
	this->img = img;
	this->id = ObjectID::abyss;
	collision = new Collision(0, 0, 32, 32);
}

int Abyss::update(const Collision & playerCol) {
	collision->updatePos(x, y);
	return 0;
}

void Abyss::Draw(int drawX, int drawY) {
	//ŒŠ‚È‚Ì‚Å‚Æ‚­‚É‰æ‘œ‚Í‚È‚¢H
	DrawBox(x - drawX, y - drawY, x - drawX+32, y - drawY+32, 0xFF00FF, true);
}

void Abyss::collisionCheck(const Collision & target) {}
