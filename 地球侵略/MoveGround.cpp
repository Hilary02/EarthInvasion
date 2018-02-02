#include "MoveGround.h"

MoveGround::MoveGround() {}

MoveGround::~MoveGround() {}

MoveGround::MoveGround(double x, double y, double moveUp, double moveDown, char xory, int img) {
	this->x = x;
	this->y = y;
	this->moveX = x;
	this->moveY = y;
	this->moveUp = moveUp * 64;
	this->moveDown = moveDown * 64;
	this->xory = xory;
	this->imgGround = img;
	collision = new Collision(0, -MOVE, 64, 16);
}

int MoveGround::update(const Collision & playerCol) {
	//ここでは動くだけで当たり判定はせず，Player自身で判定と座標の処理を行う．
	Move();
	collision->updatePos(moveX, moveY);
	return 0;
}

void MoveGround::Draw(int drawX, int drawY) {
	DrawGraph(moveX - drawX, moveY - drawY, imgGround, true);

	//当たり判定領域の表示
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