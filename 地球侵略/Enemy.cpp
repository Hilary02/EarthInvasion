#include "Enemy.h"
#include "DxLib.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

Enemy::Enemy(int x, int y, int img, int id, ICollisionManager* IcolMgr){
	this->x = x;
	this->y = y;
	this->imgHandle = img;
	this->enemyID = id;
	LoadDivGraph("data/img/enemy1Walk.png", 8, 4, 2, 64, 64, walkHundle);
	LoadDivGraph("data/img/enemy1Atack.png", 4, 4, 1, 64, 64, atackHundle);
	LoadDivGraph("data/img/enemy1Die.png", 8, 4, 2, 64, 64, deadHundle);
	bulletHundle = LoadGraph("data/img/bullet.png");
	collision = new Collision(colXOffset, colYOffset, colXSize, colYSize);
	AttackBox = new Collision(32, colYOffset, -160, colYSize);

	this->IcolMgr = IcolMgr;
}

//Enemy::Enemy(int x, int y, int img, int id,) {
//	this->x = x;
//	this->y = y;
//	this->imgHandle = img;
//	this->enemyID = id;
//	LoadDivGraph("data/img/enemy1Walk.png", 8, 4, 2, 64, 64, walk);
//	HitAction = hit;
//}

int Enemy::update(const Collision & playerCol)
{
	ct++;
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
				bullets.erase(bullets.begin()+index);
			}
		}
		index = -1;
	}


	return 0;

}

void Enemy::Draw(int drawX, int drawY)
{

	//d	DrawFormatString(0, 0, 0xFFFFFF, "Enemy:%d,%d     Draw:%d,%d", x, y, x - drawX, y - drawY);

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

	if (!dead)
	{
		for (auto &bull : bullets)
		{
			bull->Draw(drawX, drawY);
		}
	}
}

void Enemy::collisionCheck(const Collision & target) {
	int isCol = collision->doCollisonCheck((target.hitRange));
	int attackR = AttackBox->doCollisonCheck((target.hitRange));
	if (isCol) {

		//d 		DrawBox(10, 20, 100, 200, 0xFF0000, true);
		if (!dead)IcolMgr->requestAction(Action::DmgPlayer);
		//IcolMgr->requestAction(Action::DmgPlayer);
		modHp(mod);
	}
	else if (attackR) {
		//d 		DrawBox(10, 20, 100, 200, 0xFF0000, false);

		movedis = 0;
		//d DrawBox(10, 20, 100, 200, 0xFF0000, true);


		//d DrawBox(10,20,100,200, 0x0000ff,true);
		AtackCommon();
	}
	else {
	//d	DrawBox(10, 20, 100, 200, 0xFF0000, false);
		MoveCommon();

	}
}

void Enemy::MoveCommon()
{
	movedis = 1;
	//?͋Z?Ȃ̂ł??ƂŏC???i???S???ɂ͈ړ????Ȃ??j
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

	//count???Z?b?g????
	//if (drawcount == 72) drawcount = 0;
}

void Enemy::AtackCommon()
{
	movedis = 0;
	imgHandle = atackHundle[(drawcount / 12) % 4];
	drawcount += addCount;
	if (ct > 180)
	{
		ct = 0;
		Bullet* objBull = new Bullet(x, y, bulletHundle, isRight, IcolMgr);
		bullets.push_back(objBull);
	}
	//drawcount++;
}

void Enemy::DeadCheck()
{
	if(getHp() < 0){
		if (!dead) drawcount = 0, dead = true;
		if (drawcount > 84) addCount = 0;
		imgHandle = deadHundle[(drawcount / 12) % 8];
		drawcount += addCount;
	}

}

bool Enemy::IsRangeCheck()
{
	dis += movedis;
	if (moveRange < dis)
	{
		dis = 0;
		AttackBox->flip();
		return !isRight;
	}
	else
	{
		return isRight;
	}
}


