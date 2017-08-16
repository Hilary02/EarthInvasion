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
void Root::setPos(double modX, double modY){
	this->x = modX;
	this->y = modY;
}
