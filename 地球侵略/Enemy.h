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
	Enemy(int x, int y, int img, int id, IObjectManager* Iobj);
	
	int update(const Collision & playerCol) override;
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
	int atkCt = 181;
	int HpCt = 61;
	int count = 0;  // enemyのdrawcountを所々でplayerの様に0に戻すとこれいらない
	bool isPlayerAtk = false;
	bool isRight = false;
	bool dead = false;
	
	int index = -1;
	bool rangeFlg;

	std::vector<Bullet*> bullets;

	Collision* AttackBox;
	bool remove = false;
	int removeCount = 70;
};

