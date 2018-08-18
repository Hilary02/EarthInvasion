#include "Goal.h"
#include "DxLib.h"
#include "SceneManager.h"
#include "IStageBase.h"

Goal::Goal(int x, int y, int handle, int stageID, IStageBase* stage) {
	this->x = x;
	this->y = y;
	this->imgHandle = handle;
	this->stageId = stageID;
	this->Istage = stage;
	this->id = ObjectID::goal;
	collision = new Collision(16, 0, 2, 64);
	LoadDivGraph("data/img/goal/UFO_Sample.png", 4, 4, 1, 96, 288, img_ufo);
}

Goal::~Goal() {}

int Goal::update(const Collision & playerCol) {
	counter++;
	collision->updatePos(x, y);
	imgHandle = img_ufo[(counter / 25) % 4];
	int isCol = collision->doCollisonCheck((playerCol.hitRange));
	if (isCol == 1) {
		//‚ß‚¿‚á‚­‚¿‚á
		savedata.setClearFlag(stageId, 1);
		savedata.save();
		Istage->PlayAnimation(clearAnime);	//ƒNƒŠƒA‰‰o‚É“ü‚é
	}
	return 0;
}

void Goal::Draw(int drawX, int drawY) {
	DrawGraph(x - drawX - 32, y - drawY - 256, imgHandle, true);
}

