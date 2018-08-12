#include "BGMChanger.h"
#include "SoundManager.h"


BGMChanger::BGMChanger() {}
BGMChanger::~BGMChanger() {}

BGMChanger::BGMChanger(int x, int y) {
	this->x = x;
	this->y = y;
	this->id = ObjectID::bgmChanger;

	collision = new Collision(0, 0, 64, 64);
}

int BGMChanger::update(const Collision & playerCol) {
	collision->updatePos(x, y);
	return collisionCheck(playerCol);
}

void BGMChanger::Draw(int drawX, int drawY) {}

int BGMChanger::collisionCheck(const Collision & target) {
	int isCol = collision->doCollisonCheck((target.hitRange));
	if (isCol) {
		SoundM.SetMusic(LoadSoundMem("data/mc/bossA_boss.ogg"));
		return -1;
	}
	else {
		return 0;
	}
}