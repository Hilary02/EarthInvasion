#include "AntiAlienLaser.h"



AntiAlienLaser::AntiAlienLaser()
{
}


AntiAlienLaser::~AntiAlienLaser()
{
}

AntiAlienLaser::AntiAlienLaser(int x, int y, int hundle, ObjectID id)
{
	this->x = x;
	this->y = y;
	this->imgHandle = hundle;
	this->id = id;

	collision = new Collision(x, y, 128, 256);
}
