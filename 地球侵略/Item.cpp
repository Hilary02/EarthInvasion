#include "Item.h"



Item::Item()
{
}


Item::~Item()
{
}

Item::Item(int x, int y, int img)
{
	this->x = x;
	this->y = y;
	this->imgHandle = img;
	this->id = ObjectID::healPot;

	collision = new Collision(0, 0, 32, 32);
}

int Item::update(const Collision & playerCol)
{
	collision->updatePos(x, y);
	int n = collisionCheck(playerCol);
	return n;
}

void Item::Draw(int drawX, int drawY)
{
	DrawGraph(x - drawX, y - drawY, imgHandle, true);
}

int Item::collisionCheck(const Collision & target) {
	int isCol = collision->doCollisonCheck((target.hitRange));
	if (isCol) {
		//delete this;
		return -1;
	}
	else {
		return 0;
	}
}