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


// マップにおいての絶対座標を指定するとその座標に設定
void Root::setAbsolutePos(double modX, double modY){
	this->x = modX;
	this->y = modY;
}

//移動量を設定すると引数の値を移動した位置へ移動
void Root::setRelativePos(double modX, double modY) {
	this->x += modX;
	this->y += modY;
}