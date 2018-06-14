#pragma once
#include "Object.h"
class Abyss :
	public Object
{
public:
	Abyss();
	~Abyss();
	Abyss(int x, int y, int img);
	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
	void collisionCheck(const Collision& target);
private:
	int x;
	int y;
	int img;
};

