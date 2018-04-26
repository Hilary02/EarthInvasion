#pragma once
#include "DxLib.h"
#include "Object.h"
class Spark :
	public Object
{
public:
	Spark();
	~Spark();
	Spark(int x, int y, int img);
	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
	void collisionCheck(const Collision& target);
private:
	int x;
	int y;
	int imgSpark;
	int frame;
};

