#include "MoveGround.h"



MoveGround::MoveGround()
{
}


MoveGround::~MoveGround()
{
}

MoveGround::MoveGround(int x, int y, int moveUp, int moveDown, char xory, int img) {
	this->x = x;
	this->y = y;
	this->moveX = x;
	this->moveY = y;
	this->moveUp = moveUp * 64;
	this->moveDown = moveDown * 64;
	this->xory = xory;
	this->imgGround = img;
}
void MoveGround::Update(){
	Move();
}

void MoveGround::Draw(int drawX, int drawY) {
	DrawGraph(moveX - drawX, moveY - drawY, imgGround, true);

}

void MoveGround::Move() {
	MoveCheck();
	if (xory)
	{
		if (isXorY) {
			moveX -= MOVE;
		}
		else {
			moveX += MOVE;
		}
	}
	else
	{
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
	else if(moveY < y - moveUp || moveY > y + moveDown){
		isXorY = !isXorY;
	}
}