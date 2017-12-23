#pragma once
#include "Object.h"
class Goal :
	public Object
{
public:


	Goal(int x, int y, int handle, ICollisionManager* IcolMgr);
	~Goal();
	int update(const Collision & playerCol);
	void Draw(int drawX, int drawY);

private:
	Collision* collision;

};

