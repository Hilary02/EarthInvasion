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
	void Draw(int x, int y);
	int enemyID;

private:
	int moveRange;
	const int MOVE = 2;
};

