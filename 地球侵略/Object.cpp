#include "Object.h"

Object::Object()
{
}

Object::Object(int x, int y, int handle) {

}

Object::~Object()
{
}

void Object::Update(Collision playerCol)
{
}


void Object::Draw(int drawX, int drawY)
{
}

void Object::collisionCheck()
{
}

// �}�b�v�ɂ����Ă̐�΍��W���w�肷��Ƃ��̍��W�ɐݒ�
void Object::setAbsolutePos(int modX, int modY) {
	this->x = modX;
	this->y = modY;
}

//�ړ��ʂ�ݒ肷��ƈ����̒l���ړ������ʒu�ֈړ�
void Object::setRelativePos(int modX, int modY) {
	this->x += modX;
	this->y += modY;
}