#pragma once

/*
Offset�ɂ͉摜���_���画��̎n�_�����炷�l���C
Size�ɂ�Offset���N�_�Ƃ����l������D
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
};