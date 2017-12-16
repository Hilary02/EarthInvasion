#include "Collision.h"

Collision::Collision(int xOffset, int yOffset, int xSize, int ySize) {
	HitRange range;
	range.xOffset = xOffset;
	range.yOffset = yOffset;
	range.xSize = xSize;
	range.ySize = ySize;
	hitRange = &range;
}

Collision::~Collision()
{
}

void Collision::updatePos(int x, int y) {
	hitRange->xPos = x;
	hitRange->yPos = y;
}

int Collision::doCollisonCheck(const HitRange& target) {
	int tX1 = target.xPos + target.xOffset;
	int tX2 = target.xPos + target.xOffset + target.xSize;
	int tY1 = target.yPos + target.yOffset;
	int tY2 = target.yPos + target.yOffset + target.ySize;

	int mX1 = hitRange->xPos + hitRange->xOffset;
	int mX2 = hitRange->xPos + hitRange->xOffset + hitRange->xSize;
	int mY1 = hitRange->yPos + hitRange->yOffset;
	int mY2 = hitRange->yPos + hitRange->yOffset + hitRange->ySize;

	if ((tX1 < mX2) && (tX2 > mX1) &&
		(tY1 < mY2) && (tY2 > mY1)) {
		/*�������Ă����ꍇ�Ɏ��s����鏈���͌Ăяo�����ŏ���*/
		return 1;
	}
	else {
		return 0;

	}
}
