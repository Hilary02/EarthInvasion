#include "Collision.h"
//#include "DxLib.h"  //デバッグ表示をしたいなら追加

Collision::Collision(){}

Collision::Collision(int xOffset, int yOffset, int xSize, int ySize) {
	hitRange.xOffset = xOffset;
	hitRange.yOffset = yOffset;
	hitRange.xSize = xSize;
	hitRange.ySize = ySize;
}

Collision::~Collision(){}

void Collision::updatePos(int x, int y) {
	hitRange.xPos = x;
	hitRange.yPos = y;
}

void Collision::xFlip(){
	hitRange.xSize= -hitRange.xSize;
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
	if ((tX1 < mX2) && (tX2 > mX1) &&
		(tY1 < mY2) && (tY2 > mY1)) {
		/*当たっていた場合に実行される処理は呼び出し元で書く*/
		return 1;
	}
	else {
		return 0;

	}
}
