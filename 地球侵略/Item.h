#pragma once
#include "Object.h"
#include <map>
class Item :
	public Object
{
public:
	Item();
	~Item();
	Item(int x, int y, int img, ICollisionManager* IcolMgr);
	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
	int collisionCheck(const Collision& target);
};
