#include "AntiAlienLaser.h"
#include "DxLib.h"
#include "SoundManager.h"


AntiAlienLaser::AntiAlienLaser()
{
}


AntiAlienLaser::~AntiAlienLaser()
{
}

AntiAlienLaser::AntiAlienLaser(int x, int y, int hundle, ObjectID id)
{
	LoadImg();
	this->x = x;
	this->y = y;
	this->imgHandle = hundle;
	this->id = id;

	collision = new Collision(0, 0, 128, 256);


}

int AntiAlienLaser::update(const Collision &pl) {
	collision->updatePos(x, y);
	if (abs(pl.hitRange.xPos - this->x) <= 400) {
		timer++;
	}
	else {
		timer = 0;
	}

	if (timer > 240 && timer < 420) {
		collision->updatePos(x + 9, y);
		collision->hitRange.xSize = 46;
		collision->hitRange.ySize = 352;
	}
	else {
		collision->updatePos(x, y);
		collision->hitRange.xSize = 64;
		collision->hitRange.ySize = 32;
	}
	return 1;
}



void AntiAlienLaser::Draw(int drawX, int drawY)
{
	int tempX = x - drawX;
	int tempY = y - drawY;

	if (timer <= 240) {
		DrawGraph(tempX, tempY, laserImg[0], TRUE);
		if (timer >= 60) {
			DrawGraph(tempX, tempY + 32, laserImg[(timer - 60) / 5 % 4 + 20], TRUE);
		}
	}
	else {
		DrawGraph(tempX, tempY, laserImg[1], TRUE);
		for (int i = 0; i < 5; i++) {
			SoundM.Se("data/se/laser.wav");
			DrawGraph(tempX, tempY + i * 64 + 32, laserImg[(timer - 240) / 15 % 4 + 5], TRUE);
		}
		if (timer >= 420)
			timer = 0;
	}
/*	DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX,
		collision->hitRange.yPos + collision->hitRange.yOffset - drawY,
		collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX,
		collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY,
		0xFF00FF, false);*/
}

void AntiAlienLaser::LoadImg() {
	LoadDivGraph("data/img/LaserA_Wait.png", 1, 1, 1, 64, 32, laserImg);
	LoadDivGraph("data/img/LaserA_Shoot.png", 1, 1, 1, 64, 32, &laserImg[1]);
	LoadDivGraph("data/img/LaserBeemA.png", 4, 4, 1, 64, 64, &laserImg[5]);
	LoadDivGraph("data/img/LaserB_Wait.png", 1, 1, 1, 32, 64, &laserImg[10]);
	LoadDivGraph("data/img/LaserB_shoot.png", 1, 1, 1, 32, 64, &laserImg[11]);
	LoadDivGraph("data/img/LaserBeemB.png", 4, 4, 1, 64, 64, &laserImg[15]);
	LoadDivGraph("data/img/LaserA_Charge.png", 4, 1, 4, 64, 32, &laserImg[20]);
}
