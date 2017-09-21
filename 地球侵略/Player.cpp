#include "Player.h"
#include "WindowData.h"
#include "KeyManager.h"

#define MOVE 1

Player::Player()
{
}

Player::Player(int x, int y) {
	this->x = x;
	this->y = y;
	this->hp = 15;

	//�摜�ǂݍ���
	//��l���j���[�g����
	LoadDivGraph("data/img/eeyanWait.png", 4, 4, 1, 64, 64, wait);
	//��l�����s
	LoadDivGraph("data/img/eeyanMove.png", 4, 4, 1, 64, 64, move);
	//��l���U��
	LoadDivGraph("data/img/eeyanAttack.png", 8, 4, 2, 64, 64, attack);
	//��l�����S
	LoadDivGraph("data/img/eeyanDie.png", 16, 4, 4, 64, 64, attack);
}

Player::~Player()
{
}

//�v�Z����
void Player::Update()
{
	if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
		x -= MOVE;
		right = false;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
		x += MOVE;
		right = true;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 1 && !jump)
		liquid = true;
	else if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 0)
		liquid = false;

	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 && !liquid) {
		jump = true;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_A) >= 1) {

	}
	if (keyM.GetKeyFrame(KEY_INPUT_S) >= 1) {

	}
	if (keyM.GetKeyFrame(KEY_INPUT_E) >= 1) {

	}

	if (jump) {
	}
	if (hp <= 0) {
		deadFlag = true;
		//GameOver();
	}

}

void Player::Draw(int drawX, int drawY)
{
	int i;
	int tempX = x - drawX, tempY = y - drawY;

	if (right) {
		if (jump) {
			switch (plState) {
			case 'N':
				break;
			}
		}
		else if (liquid) {
			i = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4;
			DrawGraph(tempX, tempY, move[i], TRUE);//��
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
			i = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
			switch (plState) {
			case 'N':
				DrawGraph(tempX, tempY, move[i], TRUE);
				break;
			}
		}
		else {
			i = 0; 
			switch (plState) {
			case 'N':
				DrawGraph(tempX, tempY, wait[i], TRUE);
				break;
			}
			if (i == 60) i = 0;
		}
	}
	else {
		if (jump) {
			switch (plState) {
			case 'N':
				break;
			}
		}
		else if (liquid) {
			i = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4;
			DrawTurnGraph(tempX, tempY, move[i], TRUE);//��
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
			i = keyM.GetKeyFrame(KEY_INPUT_LEFT) / 15 % 4;
			switch (plState) {
			case 'N':
				DrawTurnGraph(tempX, tempY, move[i], TRUE);
				break;
			}
		}
		else {
			i = 0;
			switch (plState) {
			case 'N':
				DrawTurnGraph(tempX, tempY, wait[i], TRUE);
				break;
			}
			if (i == 60) i = 0;
		}
	}
}

void Player::MapHitCheck()
{

}

void Player::EnemyHitCheck()
{
	//EnemyManeger();
}

