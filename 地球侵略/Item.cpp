#include "Item.h"



Item::Item()
{
}


Item::~Item()
{
}

Item::Item(int x, int y, int img, ICollisionManager* IcolMgr)
{
	this->x = x;
	this->y = y;
	this->imgHandle = img;
	collision = new Collision(0, 0, 64, 64);
	this->IcolMgr = IcolMgr;
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
		
		IcolMgr->requestAction(Action::HealPlayer);
		//•Û—¯
		//delete this;
		return -1;
	}
	else {
		//d DrawBox(10, 20, 100, 200, 0xFF0000, false);
		return 0;
	}
}