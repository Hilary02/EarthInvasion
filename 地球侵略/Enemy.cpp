#include "Enemy.h"
#include "DxLib.h"
#include "ObjectManager.h"
#include "KeyManager.h"

Enemy::Enemy() {}

Enemy::~Enemy() {
	delete AttackBox;
}

Enemy::Enemy(int x, int y, int img, ObjectID id, IObjectManager* Iobj) {
	this->IobjMgr = Iobj;
	this->x = x;
	this->y = y;
	this->imgHandle = img;
	this->id = id;
	if (id == ObjectID::soldierA)
	{
		setHp(3);
		setAtk(3);
	}
	LoadDivGraph("data/img/enemy1Walk.png", 8, 4, 2, 64, 64, walkHundle);
	LoadDivGraph("data/img/enemy1Atack.png", 4, 4, 1, 64, 64, atackHundle);
	LoadDivGraph("data/img/enemy1Die.png", 8, 4, 2, 64, 64, deadHundle);
	bulletHundle = LoadGraph("data/img/bullet.png");
	collision = new Collision(16, 0, 20, 64);
	AttackBox = new Collision(32, colYOffset, -160, colYSize);
}

int Enemy::update(const Collision & playerCol) {
	atkCt += addCount;
	HpCt += addCount;
	collision->updatePos(x, y);
	AttackBox->updatePos(x, y);
	collisionCheck(playerCol);

	DeadCheck();
	if (!dead)
	{
		for (auto &bull : bullets)
		{
			index++;
			if (!bull->Update())
			{
				bullets.erase(bullets.begin() + index);
			}

			if (bull->collisionCheck(playerCol))
			{
				bullets.erase(bullets.begin() + index);
			}
		}
		index = -1;
	}

	//オブジェクトとの当たり判定をとり，プレイヤー自身に影響する処理を行う
	for (auto o : IobjMgr->getObjectList()) {
		if (collision->doCollisonCheck(o->collision->hitRange)) { //当たり判定をとる
			switch (o->getId()) {
			case ObjectID::playerBullet: //プレイヤーの弾
				if (state != state::dead)modHp(-3);
				break;
			default:
				break;
			}
		}
	}

	if (dead) {
		//（死亡状態 かつ）寄生キー，接触中
		if (keyM.GetKeyFrame(KEY_INPUT_S) >= 1) {
			if (collision->doCollisonCheck((playerCol.hitRange))) {
				remove = true;
			}
		}
	}
	if (remove) {
		removeCount--;
		if (removeCount == 0) return -1;
	}

	//プレイヤーを流用．これCreatureクラスにいれるべきじゃね ？
	for (auto t : IobjMgr->getTerrainList()) {
		if (collision->doCollisonCheck(t->collision->hitRange)) {
			switch (t->getId()) {
			case ObjectID::lockedDoor: //扉
			{
				int leftTX = t->collision->hitRange.xPos + t->collision->hitRange.xOffset;
				int leftPX = collision->hitRange.xPos + collision->hitRange.xOffset;

				if (leftPX < leftTX) { x = leftTX - collision->hitRange.xSize - collision->hitRange.xOffset; }
				else if (leftPX > leftTX) { x = leftTX + t->collision->hitRange.xSize - collision->hitRange.xOffset; }
				break;
			}
			default:
				break;
			}
		}
	}
	return 0;
}

void Enemy::Draw(int drawX, int drawY) {
	DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);
	//DrawBox(AttackBox->hitRange.xPos + AttackBox->hitRange.xOffset -drawX, AttackBox->hitRange.yPos + AttackBox->hitRange.yOffset - drawY, AttackBox->hitRange.xPos + AttackBox->hitRange.xOffset - drawX+AttackBox->hitRange.xSize, AttackBox->hitRange.yPos + AttackBox->hitRange.yOffset - drawY+AttackBox->hitRange.ySize, 0x00FF00, false);

	isRight = IsRangeCheck();
	if (isRight)
	{
		DrawTurnGraph(x - drawX, y - drawY, imgHandle, true);
	}
	else
	{
		DrawGraph(x - drawX, y - drawY, imgHandle, true);
	}

}

void Enemy::collisionCheck(const Collision & target) {
	int isCol = collision->doCollisonCheck((target.hitRange));
	int attackR = AttackBox->doCollisonCheck((target.hitRange));


	if (!isPlayerAtk) {

		if (isCol && target.playerState) {
			isPlayerAtk = true;
			modHp(mod);
		}
		else if (isCol && HpCt > 60 && !target.playerState) {
			HpCt = 0;
			modHp(mod);
		}
		else if (attackR) {
			//d     DrawBox(10, 20, 100, 200, 0xFF0000, false);

			movedis = 0;
			//d DrawBox(10, 20, 100, 200, 0xFF0000, true);
			//d DrawBox(10,20,100,200, 0x0000ff,true);
			AtackCommon();
		}
		else {
			//d DrawBox(10, 20, 100, 200, 0xFF0000, false);
			MoveCommon();
		}
	}
	else
	{
		count += 1;
		if (count > 60) 
		{
			count = 0;
			isPlayerAtk = false;
		}
	}
}

void Enemy::MoveCommon()
{
	movedis = 1;
	if (dead)movedis = 0;

	if (isRight)
	{
		x += movedis;
	}
	else
	{
		x -= movedis;
	}
	imgHandle = walkHundle[(drawcount / 8) % 8];
	drawcount += addCount;

	//if (drawcount == 72) drawcount = 0;
}

void Enemy::AtackCommon()
{
	movedis = 0;
	imgHandle = atackHundle[(drawcount / 12) % 4];
	drawcount += addCount;
	if (atkCt > 180)
	{
		atkCt = 0;
		Bullet* objBull = new Bullet(x, y, bulletHundle, isRight, ObjectID::enemyBullet);
		bullets.push_back(objBull);
		IobjMgr->setObjectList(objBull);
	}
	//drawcount++;
}

void Enemy::DeadCheck() {
	if (getHp() <= 0) {
		if (!dead) drawcount = 0, dead = true;
		if (drawcount > 84) addCount = 0;
		imgHandle = deadHundle[(drawcount / 12) % 8];
		drawcount += addCount;
		state = state::dead;
		for (auto &bull : bullets)
		{
			bull->setState(-1);
		}
		bullets.clear();
	}
}

bool Enemy::IsRangeCheck() {
	dis += movedis;
	if (moveRange < dis) {
		dis = 0;
		AttackBox->xFlip();
		return !isRight;
	}
	else {
		return isRight;
	}
}

bool Enemy::getDeadState(){
	return dead;
}
