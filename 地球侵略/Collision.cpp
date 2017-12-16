#include "Collision.h"

#include "DxLib.h"

Collision::Collision()
{
}

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


	DrawFormatString(0, 200, 0xFFFFFF, "Enemy:%d,%d     Player:%d,%d",mX1,mX2, tX1, tY1);
	if ((tX1 < mX2) && (tX2 > mX1) &&
		(tY1 < mY2) && (tY2 > mY1)) {
		/*“–‚½‚Á‚Ä‚¢‚½ê‡‚ÉÀs‚³‚ê‚éˆ—‚ÍŒÄ‚Ño‚µŒ³‚Å‘‚­*/
		return 1;
	}
	else {
		return 0;

	}
}
