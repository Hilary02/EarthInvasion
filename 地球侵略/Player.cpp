#include "DxLib.h"
#include "Player.h"
#include "KeyManager.h"

Player::Player(std::vector<std::vector <int>> const &vmap) {
}

Player::Player(int x, int y) {
	this->x = x;
	this->y = y;
	this->hp = 15;
}

Player::~Player() {

}

//�v�Z����
void Player::Update() {
	if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
		right = false;
		if (MapHitCheck(-MOVE, 0)) {
			x -= MOVE;
		}
		else {
			x -= cMove;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
		right = true;
		if (MapHitCheck(MOVE, 0)) {
			x += MOVE;
		}
		else {
			x -= cMove;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 1 && !jumpFlag)
		liquidFlag = true;
	else if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 0)
		liquidFlag = false;

	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 && !liquidFlag) {
		jumpFlag = true;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_A) >= 1) {

	}
	if (keyM.GetKeyFrame(KEY_INPUT_S) >= 1) {

	}
	if (keyM.GetKeyFrame(KEY_INPUT_E) >= 1) {

	}

	if (jumpFlag) {
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

	//�E����
	if (right) {
		switch (plState) {
			
		case 'N':	//��l��
			if (jumpFlag) {
			}
			else if (liquidFlag) {
				i = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);//��
			}
			else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				i = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);
			}
			else {
				i = 0;
				DrawGraph(tempX, tempY, wait[i % 4], TRUE);
				i++;
				if (i == 60) i = 0;
			}
			break;
			
		case 'A':	//��ʕ�A
			if (jumpFlag) {

			}
			else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				i = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);
			}
			else {
				i = 0;
				DrawGraph(tempX, tempY, wait[i % 4], TRUE);
				i++;
				if (i == 60) i = 0;
			}
			break;
			
		case'B':	//��ʕ�B
			if (jumpFlag) {

			}
			else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				i = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);
			}
			else {
				i = 0;
				DrawGraph(tempX, tempY, wait[i % 4], TRUE);
				i++;
				if (i == 60) i = 0;
			}
			break;
			
		case'C':	//��ʕ�C
			if (jumpFlag) {

			}
			else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				i = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);
			}
			else {
				i = 0;
				DrawGraph(tempX, tempY, wait[i % 4], TRUE);
				i++;
				if (i == 60) i = 0;
			}
			break;
			
		case'W':	//����
			if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				i = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);
			}
			else {
				i = 0;
				DrawGraph(tempX, tempY, wait[i % 4], TRUE);
				i++;
				if (i == 60) i = 0;
			}
			break;
		}
	}
	//������
	else {
		switch (plState) {
			
		case 'N':	//��l��
			if (jumpFlag) {
			}
			else if (liquidFlag) {
				i = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);//��
			}
			else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				i = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);
			}
			else {
				i = 0;
				DrawGraph(tempX, tempY, wait[i % 4], TRUE);
				i++;
				if (i == 60) i = 0;
			}
			break;
			
		case 'A':	//��ʕ�A
			if (jumpFlag) {

			}
			else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				i = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);
			}
			else {
				i = 0;
				DrawGraph(tempX, tempY, wait[i % 4], TRUE);
				i++;
				if (i == 60) i = 0;
			}
			break;
			
		case'B':	//��ʕ�B
			if (jumpFlag) {

			}
			else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				i = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);
			}
			else {
				i = 0;
				DrawGraph(tempX, tempY, wait[i % 4], TRUE);
				i++;
				if (i == 60) i = 0;
			}
			break;
			
		case'C':	//��ʕ�C
			if (jumpFlag) {

			}
			else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				i = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);
			}
			else {
				i = 0;
				DrawGraph(tempX, tempY, wait[i % 4], TRUE);
				i++;
				if (i == 60) i = 0;
			}
			break;
			
		case'W':	//����
			if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				i = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);
			}
			else {
				i = 0;
				DrawGraph(tempX, tempY, wait[i % 4], TRUE);
				i++;
				if (i == 60) i = 0;
			}
			break;
		}
	}
	//DrawFormatString(100, 100, 0xFFFFFF, "%d,%d", tempX, tempY);
	//DrawFormatString(100, 80, 0xFFFFFF, "%d,%d", (int)x, (int)y);
}
//�摜�ǂݍ���
void Player::LoadImg()
{
	//��l���j���[�g����
	LoadDivGraph("data/img/eeyanWait.png", 4, 4, 1, 64, 64, wait);
	//��l�����s
	LoadDivGraph("data/img/eeyanMove.png", 4, 4, 1, 64, 64, move);
	//��l���W�����v
	LoadDivGraph("data/img/eeyanJump.png", 4, 4, 1, 64, 64, jump);
	//��l���U��
	LoadDivGraph("data/img/eeyanAttack.png", 8, 4, 2, 64, 64, attack);
	//��l�����S
	LoadDivGraph("data/img/eeyanDie.png", 16, 4, 4, 64, 64, die);

	//��ʕ�A
	LoadDivGraph("data/img/enemy1JumpP.png", 4, 4, 1, 64, 64, &jump[10]);

}

bool Player::MapHitCheck(int x, int y)
{
	if () {
		return true;
	}
	else {
		return false;
	}
}

void Player::EnemyHitCheck()
{
	//EnemyManeger();
}

