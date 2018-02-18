#pragma once
#include "Object.h"
class LockedDoor :
	public Object{
public:
	LockedDoor();
	~LockedDoor();
	LockedDoor(int x, int y, int img);
	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
private:
	int img;
	bool open = false;
	bool remove = false;
	void openAnimation();
	int moveTo; //–¼‘O‚Í“K“–
};

