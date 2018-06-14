#pragma once
#include "DxLib.h"
#include "Object.h"
class MoveGround :
	public Object {
public:
	MoveGround();
	~MoveGround();
	MoveGround(double x, double y, double moveup, double movedown, char xory,bool f, int img);
	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;

private:
	void Move();
	void MoveCheck();
	double x;		//座標の基準点
	double y;
	double moveUp;	//基準点からどれだけ移動できるか
	double moveDown;
	double moveX;	//現在の座標
	double moveY;
	int imgGround;
	char xory;
	const int MOVE = 1;
	bool isXorY = true;
};

