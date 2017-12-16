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


void Object::Draw(int drawX, int drawY)
{
}

void Object::collisionCheck()
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