#include "Collision.h"

#include "DxLib.h"

Collision::Collision()
{
}

Collision::Collision(int xOffset, int yOffset, int xSize, int ySize) {
	hitRange.xOffset = xOffset;
	hitRange.yOffset = yOffset;
	hitRange.xSize = xSize;
	hitRange.ySize = ySize;
}

Collision::~Collision()
{
}

void Collision::updatePos(int x, int y) {
	hitRange.xPos = x;
	hitRange.yPos = y;
}

void Collision::flip(){
	//hitRange.xOffset = -hitRange.xOffset;
	//hitRange.yOffset = -hitRange.yOffset;
	hitRange.xSize= -hitRange.xSize;
	//yhitRange.ySize  = -hitRange.ySize;

}

int Collision::doCollisonCheck(const HitRange& target) {
	int tX1 = target.xPos + target.xOffset;
	int tX2 = target.xPos + target.xOffset + target.xSize;
	int tY1 = target.yPos + target.yOffset;
	int tY2 = target.yPos + target.yOffset + target.ySize;

	int mX1 = hitRange.xPos + hitRange.xOffset;
	int mX2 = hitRange.xPos + hitRange.xOffset + hitRange.xSize;
	int mY1 = hitRange.yPos + hitRange.yOffset;
	int mY2 = hitRange.yPos + hitRange.yOffset + hitRange.ySize;

	if (mX1 > mX2) {
		int temp = mX1;
		mX1 = mX2;
		mX2 = temp;
	}
	if (mY1 > mY2) {
		int temp = mY1;
		mY1 = mY2;
		mY2 = temp;
	}

	DrawFormatString(0, 200, 0xFFFFFF, "Enemy:%d,%d     Player:%d,%d",mX1,mX2, tX1, tY1);
	
	if ((tX1 < mX2) && (tX2 > mX1) &&
		(tY1 < mY2) && (tY2 > mY1)) {
		/*�������Ă����ꍇ�Ɏ��s����鏈���͌Ăяo�����ŏ���*/
		return 1;
	}
	else {
		return 0;

	}
}
