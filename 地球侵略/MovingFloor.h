#pragma once
#include "Object.h"
class MovingFloor :
	public Object
{
public:
	MovingFloor(int x, int y, int handle, ICollisionManager* IcolMgr);
	~MovingFloor();
	void Update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
	Collision collision;
private:
	int moveSpeed = 1;
	int moveMax = 20;
	int moveMin = -20;
	int Frame = 0; //‚¢‚Â‚©‚­‚Á‚Â‚¯‚é
};

