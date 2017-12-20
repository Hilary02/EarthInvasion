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

void Item::Update(const Collision & playerCol)
{
	collision->updatePos(x, y);
	collisionCheck(playerCol);
}

void Item::Draw(int drawX, int drawY)
{

	DrawGraph(x - drawX, y - drawY, imgHandle, true);
}

void Item::collisionCheck(const Collision & target) {
	int isCol = collision->doCollisonCheck((target.hitRange));
	if (isCol) {
		
		IcolMgr->requestAction(Action::HealPlayer);
		//•Û—¯
		//delete this;
	}
	else {
		DrawBox(10, 20, 100, 200, 0xFF0000, false);
	}
}