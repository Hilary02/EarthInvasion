#include "Root.h"



Root::Root(){
	defaultX = 0;
	defaultY = 0;
	x = 0.0;
	y = 0.0;
}


Root::~Root()
{
}

void Root::Update()
{
}

void Root::Draw()
{
}


// �}�b�v�ɂ����Ă̐�΍��W���w�肷��Ƃ��̍��W�ɐݒ�
void Root::setAbsolutePos(double modX, double modY){
	this->x = modX;
	this->y = modY;
}

//�ړ��ʂ�ݒ肷��ƈ����̒l���ړ������ʒu�ֈړ�
void Root::setRelativePos(double modX, double modY) {
	this->x += modX;
	this->y += modY;
}