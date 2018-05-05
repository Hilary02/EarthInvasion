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
	Enemy(int x, int y, int img, ObjectID id, IObjectManager* Iobj);

	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
	void collisionCheck(const Collision& target);
	void MoveCommon();
	void AtackCommon();
	void DeadCheck();
	bool IsRangeCheck();
	int enemyID;
	bool getDeadState();

private:
	const int moveRange = 300;
	const int mod = -1;

	int drawcount = 0;
	int bulletHandle;
	int damegeHandle;
	int iconHandle;
	int walkHandle[8];
	int atackHandle[8];
	int deadHandle[8];
	int atackRen = -128;
	int invalidDamageTime = 60;
	int dis = 150;
	int movedis = 1;
	int addCount = 1;
	int atkCt = 181;
	int HpCt = 61;
	int count = 0;  // enemyのdrawcountを所々でplayerの様に0に戻すとこれいらない
	int counter = 0;	//カウンタ系統一したほうがいいのでは？
	int endNotice = 0xFFFFFF;
	bool drawIcon = false;
	bool isPlayerAtk = false;
	bool isRight = false;
	bool isMove = true;
	bool isAtacck = false;
	bool isNotice = false;

	int index = -1;
	//bool rangeFlg;

	std::vector<Bullet*> bullets;

	Collision* AttackBox;
	bool remove = false;
	int removeCount = 70;
};