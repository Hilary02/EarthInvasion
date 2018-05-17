#include "Enemy.h"
#include "DxLib.h"
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
		spped = 1;
		atkInterval = 104;
	}
	else if (id == ObjectID::soldierB)
	{
		setHp(15);
		setAtk(5);
		spped = 2;
		atkInterval = 52;
	}
	
	LoadDivGraph("data/img/enemy1Walk.png", 8, 4, 2, 64, 64, walkHandle);
	LoadDivGraph("data/img/enemy1WaitForAtack.png", 4, 4, 1, 64, 64, atackHandle);
	LoadDivGraph("data/img/enemy1Atack.png", 4, 4, 1, 64, 64, &atackHandle[4]);
	LoadDivGraph("data/img/enemy1Die.png", 8, 4, 2, 64	, 64, deadHandle);
	bulletHandle = LoadGraph("data/img/bullet.png");
	damegeHandle = LoadGraph("data/img/enemy1Damage.png");
	iconHandle = LoadGraph("data/img/exclamation.png");
	collision = new Collision(16, 0, 20, 64);
	AttackBox = new Collision(32, colYOffset, -160, colYSize);
	state = State::alive;
}

int Enemy::update(const Collision & playerCol) {
	DeadCheck();
	if (state == State::alive)
	{
		counter++;
		atkCt += addCount;
		HpCt += addCount;
		collision->updatePos(x, y);
		AttackBox->updatePos(x, y);
		collisionCheck(playerCol);
		isRight = IsRangeCheck();

		for (auto &bull : bullets)
		{
			index++;
			if (!bull->isOutOfRange() || bull->collisionCheck(playerCol))
			{
				bullets.erase(bullets.begin() + index);
			}

		}
		index = -1;
	}
	if (state == State::respawn
		&& abs(playerCol.hitRange.xPos - this->x) >= 600) {
		state = State::alive;
		hp = 3;
	}

	if (endNotice == 0xFFFFFF) {}
	else if (counter <= endNotice) { drawIcon = true; }
	else {
		drawIcon = false;
		isNotice = true;
	}


	//オブジェクトとの当たり判定をとり，プレイヤー自身に影響する処理を行う
	for (auto o : IobjMgr->getObjectList()) {
		if (collision->doCollisonCheck(o->collision->hitRange)) { //当たり判定をとる
			switch (o->getId()) {
			case ObjectID::playerBullet: //プレイヤーの弾
				if (state == State::alive)modHp(-3);
				break;
			default:
				break;
			}
		}
	}

	if (state == State::dead
		&& keyM.GetKeyFrame(KEY_INPUT_X) >= 1
		&& collision->doCollisonCheck((playerCol.hitRange))) {
		state = State::respawn;
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
	//DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);
	//DrawBox(AttackBox->hitRange.xPos + AttackBox->hitRange.xOffset -drawX, AttackBox->hitRange.yPos + AttackBox->hitRange.yOffset - drawY, AttackBox->hitRange.xPos + AttackBox->hitRange.xOffset - drawX+AttackBox->hitRange.xSize, AttackBox->hitRange.yPos + AttackBox->hitRange.yOffset - drawY+AttackBox->hitRange.ySize, 0x00FF00, false);
	if (state != State::respawn) {
		if (isRight)
		{
			DrawTurnGraph(x - drawX, y - drawY, imgHandle, true);
		}
		else
		{
			DrawGraph(x - drawX, y - drawY, imgHandle, true);
		}
		if (drawIcon) {
			DrawGraph(x - drawX + 20, y - drawY - 20, iconHandle, TRUE);
		}
	}

}

void Enemy::collisionCheck(const Collision & target) {
	int isCol = collision->doCollisonCheck((target.hitRange));
	int attackR = AttackBox->doCollisonCheck((target.hitRange));

	if (!isPlayerAtk) {

		if (isCol && target.playerState) {
			imgHandle = damegeHandle;
			movedis = 0;
			isPlayerAtk = true;
			modHp(mod);
		}
		else if (attackR) {
			if (isNotice) {
				movedis = 0;
				AtackCommon();
			}
			else {
				movedis = 0;
				if (endNotice == 0xFFFFFF) { endNotice = counter + 90; }
			}
		}
		else {
			//d DrawBox(10, 20, 100, 200, 0xFF0000, false);
			MoveCommon();
		}
	}
	else {
		count += 1;
		if (count > 60) {
			count = 0;
			isPlayerAtk = false;
		}
	}
}

void Enemy::MoveCommon()
{
	if (!isMove && state == State::alive)
	{
		drawcount = 0;
		isMove = true;
		isAtacck = false;
	}

	movedis = spped;
	if (state == State::dead)movedis = 0;

	if (isRight)
	{
		x += movedis;
	}	
	else
	{
		x -= movedis;
	}
	imgHandle = walkHandle[(drawcount / 8) % 8];
	if (state == State::alive) drawcount += addCount;

}

void Enemy::AtackCommon()
{
	if (!isAtacck && state == State::alive)
	{
		drawcount = 0;
		isMove = false;
		isAtacck = true;
	}
	movedis = 0;
	imgHandle = atackHandle[(drawcount / 12) % 8];
	hundleIndex = (drawcount / 12) % 8;
	if (state == State::alive) drawcount += addCount;
	if (atkCt > atkInterval && state == State::alive && hundleIndex == 5)
	{
		atkCt = 0;
		Bullet* objBull = new Bullet(x, y, bulletHandle, isRight, ObjectID::enemyBullet);
		bullets.push_back(objBull);
		IobjMgr->addObject(objBull);
	}
	if ((drawcount / 12) > 8 && hundleIndex == 0)drawcount = 0; //drawcountのリセット
}

void Enemy::DeadCheck() {
	if (this->hp <= 0 && state == State::alive) {
		state = State::dead;
		drawcount = 0;
		for (auto &bull : bullets) {
			bull->setState(-1);
		}
		bullets.clear();
	}
	if (state == State::dead) {
		if (drawcount < 84) { drawcount++; }
		imgHandle = deadHandle[(drawcount / 12) % 8];
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

bool Enemy::getDeadState() {
	if (state != State::alive) {
		return true;
	}
	else {
		return false;
	}
}
