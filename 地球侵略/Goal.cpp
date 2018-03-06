#include "Goal.h"
#include "DxLib.h"
#include "SceneManager.h"

Goal::Goal(int x, int y, int handle, int stage) {
	this->x = x;
	this->y = y;
	this->imgHandle = handle;
	this->stageId = stage;
	this->id = ObjectID::goal;
	collision = new Collision(0, 0, 64, 128);
}

Goal::~Goal() {}

int Goal::update(const Collision & playerCol) {
	collision->updatePos(x, y);
	int isCol = collision->doCollisonCheck((playerCol.hitRange));
	if (isCol == 1) {
		//‚ß‚¿‚á‚­‚¿‚á
		savedata.setClearFlag(stageId, 1);
		savedata.save();
		SceneM.ChangeScene(scene::Clear);
	}
	else {
		//d DrawBox(100, 20, 100, 200, 0xFF0000, false);
	}
	return 0;
}

void Goal::Draw(int drawX, int drawY) {
	DrawGraph(x - drawX, y - drawY, imgHandle, true);
}

