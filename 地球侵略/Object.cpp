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
		/*�������Ă����ꍇ�Ɏ��s*/
		onHit(target);
		return 1;
	}else {
		return 0;

	}
}


void Object::onHit(Object target) {
	//�v���C���[�Ɠ��������Ƃ��̓�����L�q
	
}


