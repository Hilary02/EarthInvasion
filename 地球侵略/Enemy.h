#pragma once
#include "Creature.h"
#include "Bullet.h"
#include <vector>

class Enemy :
	public Creature

{
public:
	Enemy();
	~Enemy();

	Enemy(int x, int y, int img, int id, ICollisionManager* IcolMgr);
	
	void Update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
	void collisionCheck(const Collision& target);
	void MoveCommon();
	void AtackCommon();
	void DeadCheck();
	bool IsRangeCheck();
	int enemyID;

private:
	const int moveRange = 300;
	const int mod = -1;

	int drawcount = 0;
	int bulletHundle;
	int walkHundle[8];
	int atackHundle[4];
	int deadHundle[8];
	int atackRen = -128;
	int invalidDamageTime = 60;
	int dis = 150;
	int movedis = 1;
	int addCount = 1;
	int ct = 181;
	bool isRight = false;
	bool dead = false;
	
	int index = -1;
	bool rangeFlg;

	std::vector<Bullet*> bullets;

	Collision* collision;
	Collision* AttackBox;
};

