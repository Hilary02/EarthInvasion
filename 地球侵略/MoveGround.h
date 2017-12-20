#pragma once
#include "DxLib.h"
#include "Object.h"
class MoveGround :
	public Object {
public:
	MoveGround();
	~MoveGround();
	MoveGround(int x, int y, int moveup, int movedown, char xory, int img);
	void Update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
	void Move();
	void MoveCheck();

private:
	int x;
	int y;
	int moveUp;
	int moveDown;
	int moveX;
	int moveY;
	int imgGround;
	char xory;
	const int MOVE = 1;
	bool isXorY = true;
};

