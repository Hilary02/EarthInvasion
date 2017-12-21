#include "Goal.h"
#include "DxLib.h"
#include "SceneManager.h"

Goal::Goal(int x, int y, int handle, ICollisionManager * IcolMgr){
	this->x = x;
	this->y = y;
	this->imgHandle = handle;
	this->IcolMgr = IcolMgr;
	collision = new Collision(0, 0, 64, 64);
}

Goal::~Goal()
{
}

void Goal::Update(const Collision & playerCol){
	collision->updatePos(x, y);
	int isCol = collision->doCollisonCheck((playerCol.hitRange));
	if (isCol == 1) {
		//‚ß‚¿‚á‚­‚¿‚á
		SceneM.ChangeScene(scene::Clear);
	}
	else {
		DrawBox(100, 20, 100, 200, 0xFF0000, false);
	}
}

void Goal::Draw(int drawX, int drawY){
	DrawGraph(x - drawX, y - drawY, imgHandle, true);
}

