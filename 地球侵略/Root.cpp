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


// �}�b�v�ɂ����Ă̐�΍��W���w�肷��Ƃ��̍��W�ɐݒ�
void Root::setPos(double modX, double modY){
	this->x = modX;
	this->y = modY;
}
