#include "Object.h"

Object::Object()
{
}

Object::Object(int x, int y, int handle, ICollisionManager* IcolMgr) {

}

Object::~Object()
{
}

int Object::update(const Collision & playerCol)
{
	return 0;
}

void Object::Draw(int drawX, int drawY)
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