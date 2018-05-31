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
	loadImg();
	this->x = x;
	this->y = y;
	this->imgHandle = hundle;
	this->id = id;

	collision = new Collision(x, y, 128, 256);

	
}

int AntiAlienLaser::update(const Collision &pl) {
	if (abs(pl.hitRange.xPos - this->x) >= 400) {
		timer++;
	}
	else {
		timer = 0;
	}
	return 1;
}

void AntiAlienLaser::Draw(int drawX, int drawY) {
	int tempX = x - drawX;
	int tempY = y - drawY;

	if (timer <= 240) {
		DrawGraph(tempX, tempY, laserImg[0], TRUE);
	}
	else {
		DrawGraph(tempX, tempY, laserImg[1], TRUE);
		for (int i = 0; i < 5; i++) {
			DrawGraph(tempX, tempY + i * 64 + 32, laserImg[(timer - 240) / 15 % 4 + 5], TRUE);
		}
	}
	if (timer >= 420)
		timer = 0;
	DrawGraph(tempX, tempY, laserImg[0], TRUE);
	DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX,
		collision->hitRange.yPos + collision->hitRange.yOffset - drawY,
		collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX,
		collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY,
		0xFF00FF, false);
}


void AntiAlienLaser::loadImg() {
	LoadDivGraph("data/img/LaserA_Wait.png", 1, 1, 1, 64, 32, laserImg);
	LoadDivGraph("data/img/LaserA_Shoot.png", 1, 1, 1, 64, 32, &laserImg[1]);
	LoadDivGraph("data/img/LaserBeemA.png", 4, 4, 1, 64, 64, &laserImg[5]);
	LoadDivGraph("data/img/LaserB_Wait.png", 1, 1, 1, 32, 64, &laserImg[10]);
	LoadDivGraph("data/img/LaserB_shoot.png", 1, 1, 1, 32, 64, &laserImg[11]);
	LoadDivGraph("data/img/LaserBeemB.png", 4, 4, 1, 64, 64, &laserImg[15]);
}