#pragma once
#include "Creature.h"

class Enemy :
	public Creature
	
{
public:
	Enemy();
	~Enemy();

	Enemy(int x, int y, int img, int id);
	void Update();
	void Draw();
	void MoveCommon();
	int enemyID;

private:
	int drawcount = 0;
	int walk[8];
	int moveRange  = 5;
	const int MOVE = 2;
};

