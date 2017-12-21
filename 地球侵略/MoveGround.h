#pragma once
#include "DxLib.h"
#include "Object.h"
class MoveGround :
	public Object {
public:
	MoveGround();
	~MoveGround();
	MoveGround(double x, double y, double moveup, double movedown, char xory, int img);
	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
	void Move();
	void MoveCheck();

private:
	double x;
	double y;
	double moveUp;
	double moveDown;
	double moveX;
	double moveY;
	int imgGround;
	char xory;
	const int MOVE = 1;
	bool isXorY = true;
};

