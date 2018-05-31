#pragma once
#include "DxLib.h"
#include "Object.h"

class Fire :
	public Object
{
public:
	Fire();
	~Fire();
	Fire(int x, int y, int img);
	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
	void collisionCheck(const Collision& target);
private:
	int x;
	int y;
	int imgFire;
	int frame;
	int fireHandle[4];
	int drawCount = 0;
};