#pragma once
#include "Object.h"
class BGMChanger :
	public Object
{
public:
	BGMChanger();
	~BGMChanger();
	BGMChanger(int x, int y);
	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
	int collisionCheck(const Collision& target);
};

