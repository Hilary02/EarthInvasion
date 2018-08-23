#include "MoveGround.h"

MoveGround::MoveGround() {}

MoveGround::~MoveGround() {}

MoveGround::MoveGround(double x, double y, double moveUp, double moveDown, char xory, bool f, int img) {
	this->x = x;
	this->y = y;
	this->moveX = x;
	this->moveY = y;
	this->moveUp = moveUp * 64;
	this->moveDown = moveDown * 64;
	this->xory = xory;
	this->isXorY = f;
	this->imgGround = img;
	collision = new Collision(0, -MOVE, 64, 16);
	id = ObjectID::movingFloor;
}

int MoveGround::update(const Collision & playerCol) {
	//�����ł͓��������œ����蔻��͂����CPlayer���g�Ŕ���ƍ��W�̏������s���D
	Move();
	collision->updatePos((int)moveX, (int)moveY);
	return 0;
}

void MoveGround::Draw(int drawX, int drawY) {
	DrawGraph((int)moveX - drawX, (int)moveY - drawY, imgGround, true);

	//�����蔻��̈�̕\��
	//DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);
}

void MoveGround::Move() {
	MoveCheck();
	if (xory) {
		if (isXorY) {
			moveX -= MOVE;
		}
		else {
			moveX += MOVE;
		}
	}
	else {
		if (isXorY) {
			moveY -= MOVE;
		}
		else {
			moveY += MOVE;
		}
	}
}

void MoveGround::MoveCheck() {
	if (moveX < x - moveUp || moveX > x + moveDown) {
		isXorY = !isXorY;
	}
	else if (moveY < y - moveUp || moveY > y + moveDown) {
		isXorY = !isXorY;
	}
}