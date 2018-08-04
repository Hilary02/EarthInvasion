#include "DrG.h"
#include "Bullet.h"


DrG::DrG() {}

DrG::~DrG() {}

DrG::DrG(int x, int y, int img, ObjectID id, IObjectManager * Iobj) {
	this->IobjMgr = Iobj;
	this->x = x;
	this->y = y;
	this->imgHandle = img;
	setHp(5);
	LoadDivGraph("data/img/DrG/enemy5Wait.png", 2, 2, 1, 64, 64, img_wait);
	img_damage = LoadGraph("data/img/DrG/enemy5Damage.png");
	LoadDivGraph("data/img/DrG/enemy5Die.png", 4, 4, 1, 64, 64, img_die);
	collision = new Collision(20, 16, 20, 48);
	state == State::alive;
}

int DrG::update(const Collision & playerCol) {
	collision->updatePos(x, y);
	counter++;
	invulnerable--;
	imgHandle = img_wait[0];
	if ((counter / 25) % 2 == 0) {
		imgHandle = img_wait[0];
	}
	else {
		imgHandle = img_wait[1];
	}
	//オブジェクトとの当たり判定
	for (auto o : IobjMgr->getObjectList()) {
		switch (o->getId()) {
		case ObjectID::playerBullet: //プレイヤーの弾
			if (collision->doCollisonCheck(o->collision->hitRange)) { //当たり判定をとる
				if (state == State::alive && invulnerable <= 0) {
					modHp(-((Bullet*)o)->getAtk());
					invulnerable = invulnerableTime;
				}
			}
			break;
		default:
			break;
		}
	}

	return 0;
}

void DrG::Draw(int drawX, int drawY) {
	DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);
	DrawGraph(x - drawX, y - drawY, imgHandle, true);
}
