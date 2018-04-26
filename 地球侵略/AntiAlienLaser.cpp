#include "AntiAlienLaser.h"
#include "DxLib.h"


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

void AntiAlienLaser::update(const Collision) {
	timer++;
}

void AntiAlienLaser::Draw(int drawX, int drawY) {
	int tempX = x - drawX;
	int tempY = y - drawY;

	switch (id) {
	case 1:
		if (timer) {

		}
		break;
	case 2:
		if (timer) {

		}
		break;

	}
}

void loadImg() {
	LoadDivGraph("data/img/LaserA_Wait.png", 1, 1, 1, 32, 64, laserImg);
	LoadDivGraph("data/img/LaserA_Shoot.png", 1, 1, 1, 64, 32, laserImg[1]);
	LoadDivGraph("data/img/LaserB_Wait.png", 1, 1, 1, 32, 64, laserImg[10]);
	LoadDivGraph("data/img/LaserB_shoot.png", 1, 1, 1, 32, 64, laserImg[11]);
}