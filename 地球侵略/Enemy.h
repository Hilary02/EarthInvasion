#pragma once
#include "Creature.h"

class Enemy :
	public Creature

{
public:
	Enemy();
	~Enemy();

	//Enemy(int x, int y, int img, int id);
	Enemy(int x, int y, int img, int id, ICollisionManager* IcolMgr);
	
	void Update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
	void collisionCheck(const Collision& target);
	void MoveCommon();
	bool IsRangeCheck();
	int enemyID;

private:
	int drawcount = 0;
	int walk[8];
	const int moveRange  = 300;
	int dis = 150;
	bool isRight = false;
	const int MOVE = 1;

	Collision* collision;
};

