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
	double x;		//���W�̊�_
	double y;
	double moveUp;	//��_����ǂꂾ���ړ��ł��邩
	double moveDown;
	double moveX;	//���݂̍��W
	double moveY;
	int imgGround;
	char xory;
	const int MOVE = 1;
	bool isXorY = true;
};

