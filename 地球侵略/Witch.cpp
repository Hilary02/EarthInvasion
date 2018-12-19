#include "Witch.h"


Witch::Witch(int x, int y, int img, IObjectManager* Iobj, int stageID, IStageBase* stage) {
	this->IobjMgr = Iobj;
	this->x = x;
	this->y = y;
	basePositionY = y;
	this->imgHandle = img;
	this->id = id;
	this->atkInterval = 52;

	IobjMgr->witchMoveRangeCalc(x, y, &minX, &maxX);

	setHp(5);
	setAtk(5);

	LoadDivGraph("data/img/enemy2Walk.png", 4, 4, 1, 64, 64, moveHandle);
	LoadDivGraph("data/img/enemy2WaitForAtack.png", 4, 4, 1, 64, 64, attackHandle);
	LoadDivGraph("data/img/enemy2Atack.png", 4, 4, 1, 64, 64, &attackHandle[4]);
	LoadDivGraph("data/img/enemy2Die.png", 8, 4, 2, 64, 64, deadHandle);
	damegeHandle = LoadGraph("data/img/enemy2Damage.png");
	bulletHandle = LoadGraph("data/img/bullet2.png");

	collision = new Collision(16, 0, 32, 64);
	AttackBox = new Collision(30, 0, -300, 256);
	state = State::alive;

	this->stageId = stageID;
	this->Istage = stage;
}


Witch::~Witch() {
	delete AttackBox;
}

void Witch::Draw(int drawX, int drawY) {
	//	DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);
	//	DrawBox(AttackBox->hitRange.xPos + AttackBox->hitRange.xOffset - drawX, AttackBox->hitRange.yPos + AttackBox->hitRange.yOffset - drawY, AttackBox->hitRange.xPos + AttackBox->hitRange.xOffset - drawX + AttackBox->hitRange.xSize, AttackBox->hitRange.yPos + AttackBox->hitRange.yOffset - drawY + AttackBox->hitRange.ySize, 0x00FF00, false);
	if (isRight)
	{
		DrawTurnGraph(x - drawX, y - drawY, imgHandle, true);
	}
	else
	{
		DrawGraph(x - drawX, y - drawY, imgHandle, true);
	}

}

void Witch::attack() {
	atkCt += addCount;
	HpCt += addCount;


	movedis = 0;
	imgHandle = attackHandle[(drawcount / 12) % 8];
	hundleIndex = (drawcount / 12) % 8;
	if (state == State::alive) drawcount += addCount;
	if (atkCt > atkInterval && state == State::alive && hundleIndex == 5)
	{
		atkCt = 0;
		Bullet* objBull = new Bullet(x, y, getAtk(), bulletHandle, isRight, ObjectID::enemyBullet);
		bullets.push_back(objBull);
		IobjMgr->addObject(objBull);
	}
	if ((drawcount / 12) > 8 && hundleIndex == 0) {
		drawcount = 0; //drawcount�̃��Z�b�g
		if (!isFound)
		{
			isAtacck = false;
			isMove = true;
		}
	}
}

void Witch::floating()
{

	//movedis = movespeed;
	movedis = 1;
	if (isFound)
	{
		if (x < targetX + 100 && !isRight) { movedis = 0; }
		if (x > targetX - 100 && isRight) { movedis = 0; }

		//�G�l�~�[��range�`�F�b�N�̍ۂɃv���C���[����������Ƃ��邭����o�O��͋Z�ŏC���i��Œ���
		if (dis > maxX)dis = maxX - 5;
		else if (dis < minX) dis = minX + 5;
	}
	if (state == State::dead)movedis = 0;

	if (isRight)
	{
		x += movedis;
	}
	else
	{
		x -= movedis;
	}

	imgHandle = moveHandle[(drawcount / 8) % 4];
	if (state == State::alive) drawcount += addCount;

}

void Witch::risingOrDescent()
{
	isPositionY = y > basePositionY;  //����y���W��艺�Ȃ�true
	isUnderTarget = y < targetY;   //�^�[�Q�b�g����Ȃ�true
	bool isSamePosition = (y == targetY);  //����������̓���y���W�̏ꍇtrue

	if (isUnder && isUnderTarget)
	{
		y++;
	}
	else if (!isUnder && isPositionY)
	{
		y--;
	}
	else if (isSamePosition) {
		isAtacck = true;
		isMove = false;
	}
}

void Witch::collsionCheck(const Collision & target) {
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
			isFound = true;
			targetY = target.hitRange.yPos;
			targetX = target.hitRange.xPos;
			isUnder = true;
		}
		else {
			isUnder = false;
			isFound = false;
			count += 1;
			if (count > 60) {
				count = 0;
				isPlayerAtk = false;
			}
		}
	}


}

int Witch::update(const Collision & playerCol)
{
	Enemy::DeadCheck();
	Enemy::checkObjectHit(playerCol);

	if (state == State::alive)
	{
		isRight = IsRangeCheck();
		collision->updatePos(x, y);
		AttackBox->updatePos(x, y);
		collsionCheck(playerCol);
		if (isMove)
		{
			risingOrDescent();
			floating();
		}
		else if (isAtacck)
		{
			attack();
		}
	}


	if (hp <= 0) {
		//�߂��Ⴍ����
		savedata.setClearFlag(stageId, 1);
		savedata.save();
		Istage->PlayAnimation(clearAnime);	//�N���A���o�ɓ���
	}


	return 0;
}

