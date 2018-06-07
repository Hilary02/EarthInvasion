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
	int count = 0;  // enemy��drawcount�����X��player�̗l��0�ɖ߂��Ƃ��ꂢ��Ȃ�
	int spped = 0;
	int atkInterval = 0;
	int hundleIndex = 0; //if���̉摜�z���index����Ɏg�p
	bool drawIcon = false;
	bool isPlayerAtk = false;
	bool isRight = false;
	bool isMove = true;
	bool isAtacck = false;

	int  noticed = 0;	//������񔭌��֌W�B0=�������A1=�C�Â����A2=�C�Â���
	int noticeCount = 0;

	int index = -1;

	std::vector<Bullet*> bullets;

	Collision* AttackBox;
	bool remove = false;	//���X�|�[���֘A
	int removeCount = 65;
};