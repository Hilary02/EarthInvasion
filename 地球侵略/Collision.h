#pragma once

/*
Offsetには画像原点から判定の始点をずらす値を，
SizeにはOffsetを起点とした値を入れる．
*/
class HitRange {
public:
	int xPos;
	int yPos;
	int xOffset;
	int yOffset;
	int xSize;
	int ySize;
};

class Collision
{
public:
	Collision();
	Collision(int xOffset,int yOffset,int xSize,int ySize);
	~Collision();
	HitRange* hitRange;
	void updatePos(int x, int y);
	int doCollisonCheck(const HitRange& target);
	int id;
};