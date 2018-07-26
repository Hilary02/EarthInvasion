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
	int moveRange = 300;
	int minX = 0;
	int maxX = 0;
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
	int dis = 0;
	int movedis = 1;
	int addCount = 1;
	int atkCt = 181;
	int HpCt = 61;
	int count = 0;  // enemyのdrawcountを所々でplayerの様に0に戻すとこれいらない
	int movespeed = 0;
	int atkInterval = 0;
	int hundleIndex = 0; //if文の画像配列のindex判定に使用
	bool drawIcon = false;
	bool isPlayerAtk = false;
	bool isRight = false;
	bool isMove = true;
	bool isAtacck = false;

	int  noticed = 0;	//ええやん発見関係。0=未発見、1=気づき中、2=気づき済
	int noticeCount = 0;

	int index = -1;

	int rct = 100; //エネミーのrangeチェックの際にプレイヤーが発見するとくるくる回るバグを力技で修正（後で直す

	std::vector<Bullet*> bullets;

	Collision* AttackBox;
	bool remove = false;	//リスポーン関連
	int removeCount = 65;
};