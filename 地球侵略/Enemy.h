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
	int bulletHundle;
	int damegeHundle;
	int walkHundle[8];
	int atackHundle[8];
	int deadHundle[8];
	int atackRen = -128;
	int invalidDamageTime = 60;
	int dis = 150;
	int movedis = 1;
	int addCount = 1;
	int atkCt = 181;
	int HpCt = 61;
	int count = 0;  // enemy��drawcount�����X��player�̗l��0�ɖ߂��Ƃ��ꂢ��Ȃ�
	bool isPlayerAtk = false;
	bool isRight = false;
	bool dead = false;
	bool isMove = true;
	bool isAtacck = false;
	
	int index = -1;
	//bool rangeFlg;

	std::vector<Bullet*> bullets;

	Collision* AttackBox;
	bool remove = false;
	int removeCount = 70;
};

