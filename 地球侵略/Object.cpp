#include "Object.h"

Object::Object()
{
}

Object::Object(int x, int y, int handle) {

}

Object::~Object()
{
}

void Object::Update()
{
}


void Object::Draw()
{
}

// マップにおいての絶対座標を指定するとその座標に設定
void Object::setAbsolutePos(int modX, int modY) {
	this->x = modX;
	this->y = modY;
}

//移動量を設定すると引数の値を移動した位置へ移動
void Object::setRelativePos(int modX, int modY) {
	this->x += modX;
	this->y += modY;
}


int Object::hitCheck(Object target) {
	const int size = 64;
	float tMargin = (1 - target.collisionSize) / 2;
	float mMargin = (1 - collisionSize) / 2;

	int tX1 = target.x*(1 + tMargin);
	int tX2 = target.x + size* target.collisionSize;
	int tY1 = target.y*(1 + tMargin);
	int tY2 = target.y + size* target.collisionSize;

	int mX1 = x*(1 + mMargin);
	int mX2 = x + size* collisionSize;
	int mY1 = y*(1 + mMargin);
	int mY2 = y + size* collisionSize;

	if ((tX1 < mX2) && (tX2 > mX1) &&
		(tY1 < mY2) && (tY2 > mY1)) {
		/*当たっていた場合に実行*/
		onHit(target);
		return 1;
	}else {
		return 0;

	}
}


void Object::onHit(Object target) {
	//プレイヤーと当たったときの動作を記述
	
}


