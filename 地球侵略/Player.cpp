#include "DxLib.h"
#include "Player.h"
#include "KeyManager.h"

Player::Player(const std::vector<std::vector <int>> &vmap) :vmap(vmap) {
	this->hp = 15;
	LoadImg();
}


Player::Player(int x, int y) {
	this->x = x;
	this->y = y;
	this->hp = 15;
	LoadImg();
}

Player::~Player() {

}

//�v�Z����
void Player::Update() {
	if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1 && !attackFlag) {
		right = false;
		if (MapHitCheck(-MOVE, 0)) {
			x -= MOVE;
		}
		else {
			x -= cMove;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1 && !attackFlag) {
		right = true;
		if (MapHitCheck(MOVE, 0)) {
			x += MOVE;
		}
		else {
			x += cMove;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 1 && !jumpFlag && !attackFlag)
		liquidFlag = true;
	else if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 0)
		liquidFlag = false;

	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 && !liquidFlag && !attackFlag) {
		jumpFlag = true;
		jumpPower = -10;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_A) == 1 && !attackFlag) {
		attackFlag = true;
		//rect();
		drawCount = 0;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_S) >= 1) {

	}
	if (keyM.GetKeyFrame(KEY_INPUT_E) >= 1) {

	}

	if (MapHitCheck(0, 1) && MapHitCheck(0, 1)) {
		jumpFlag = true;
	}
	else {
		jumpFlag = false;
	}

	if (jumpFlag) {
		if (MapHitCheck(0, jumpPower)) {
			y += jumpPower;
			jumpPower += 1;
		}
		else {
			y += cMove;
		}

	}
	if (hp <= 0) {
		deadFlag = true;
		//GameOver();
	}

}

bool Player::MapHitCheck(int moveX, int moveY)
{
	//DrawFormatString(100, 100, 0x00, "%d,%d", ((int)this->y + moveY)/32, ((int)this->x + moveX)/32);
	//DrawFormatString(100, 120, 0x00, "%d", vmap[((int)this->y + moveY) / 32][((int)this->x + moveX) / 32]);
	switch (vmap[((int)this->y + moveY) / 32 + 4][((int)this->x + moveX) / 32+5]) {
	case 0:
		return true;
		break;
	case 1:
		if (moveX > 0)
			cMove = moveX - ((int)this->x + moveX) % 32;
		else if (moveX < 0)
			cMove = (int)this->x % 32;
		return false;
		break;
	case 2:
		if (moveX > 0)
			cMove = moveX - ((int)this->x + moveX) % 32;
		else if (moveX < 0)
			cMove = (int)this->x % 32;

		if (moveY > 0)
			cMove = moveY - ((int)this->y + moveY) % 32;
		else if (moveY < 0) {
			cMove = (int)this->y % 32;
			jumpPower = 0;
		}
			return false;
		break;
	case 5:
		return true;
		break;
	case 9:
		cMove = moveY - ((int)this->y + moveY) % 32;
		return false;
		break;
	default:
		return true;
		break;
	}
	return false;
}

void Player::Draw(int drawX, int drawY)
{
	int tempX = x - drawX, tempY = y - drawY;

	//�E����
	if (right) {
		switch (plState) {

		case 'N':	//��l��
			if (jumpFlag) {
				if (jumpPower <= 1 && jumpPower >= -1)
					DrawGraph(tempX, tempY, jump[1], TRUE);
				else if (jumpPower > 1)
					DrawGraph(tempX, tempY, jump[0], TRUE);
				else if (jumpPower < -1)
					DrawGraph(tempX, tempY, jump[2], TRUE);
			}
			else if (liquidFlag) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4;
				DrawGraph(tempX, tempY, wait[drawCount], TRUE);//��
			}
			else if (attackFlag) {
				DrawGraph(tempX, tempY, attack[drawCount / 8 % 8], true);
				drawCount++;
				if(drawCount >= 64) attackFlag = false;
			}
			else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[drawCount], TRUE);
			}
			else {
				if (drawCount > 60) drawCount = 0;
				DrawGraph(tempX, tempY, wait[drawCount /15 % 4], TRUE);
				drawCount++;
			}
			break;

		case 'A':	//��ʕ�A
			if (jumpFlag) {

			}
			else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[drawCount], TRUE);
			}
			else {
				drawCount = 0;
				DrawGraph(tempX, tempY, wait[drawCount % 4], TRUE);
				drawCount++;
				if (drawCount == 60) drawCount = 0;
			}
			break;

		case'B':	//��ʕ�B
			if (jumpFlag) {

			}
			else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[drawCount], TRUE);
			}
			else {
				drawCount = 0;
				DrawGraph(tempX, tempY, wait[drawCount % 4], TRUE);
				drawCount++;
				if (drawCount == 60) drawCount = 0;
			}
			break;

		case'C':	//��ʕ�C
			if (jumpFlag) {

			}
			else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[drawCount], TRUE);
			}
			else {
				drawCount = 0;
				DrawGraph(tempX, tempY, wait[drawCount % 4], TRUE);
				drawCount++;
				if (drawCount == 60) drawCount = 0;
			}
			break;

		case'W':	//����
			if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[drawCount], TRUE);
			}
			else {
				drawCount = 0;
				DrawGraph(tempX, tempY, wait[drawCount % 4], TRUE);
				drawCount++;
				if (drawCount == 60) drawCount = 0;
			}
			break;
		}
	}
	//������
	else if (!right) {
		switch (plState) {

		case 'N':	//��l��
			if (jumpFlag) {
				if (jumpPower <= 1 && jumpPower >= -1)
					DrawTurnGraph(tempX, tempY, jump[1], TRUE);
				else if (jumpPower > 1)
					DrawTurnGraph(tempX, tempY, jump[0], TRUE);
				else if (jumpPower < -1)
					DrawTurnGraph(tempX, tempY, jump[2], TRUE);
			}
			else if (liquidFlag) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4;
				DrawTurnGraph(tempX, tempY, wait[drawCount], TRUE);//��
			}
			else if (attackFlag) {
				DrawTurnGraph(tempX, tempY, attack[drawCount / 8 % 8], true);
				drawCount++;
				if (drawCount >= 64) attackFlag = false;
			}
			else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_LEFT) / 15 % 4;
				DrawTurnGraph(tempX, tempY, move[drawCount], TRUE);
			}
			else {
				if (drawCount > 60) drawCount = 0;
				DrawTurnGraph(tempX, tempY, wait[drawCount / 15 % 4], TRUE);
				drawCount++;
			}
			break;

		case 'A':	//��ʕ�A
			if (jumpFlag) {

			}
			else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_LEFT) / 15 % 4;
				DrawTurnGraph(tempX, tempY, move[drawCount], TRUE);
			}
			else {
				if (drawCount == 60) drawCount = 0;
				DrawTurnGraph(tempX, tempY, wait[drawCount % 4], TRUE);
				drawCount++;
			}
			break;

		case'B':	//��ʕ�B
			if (jumpFlag) {

			}
			else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_LEFT) / 15 % 4;
				DrawTurnGraph(tempX, tempY, move[drawCount], TRUE);
			}
			else {
				if (drawCount == 60) drawCount = 0;
				DrawTurnGraph(tempX, tempY, wait[drawCount % 4], TRUE);
				drawCount++;
			}
			break;

		case'C':	//��ʕ�C
			if (jumpFlag) {

			}
			else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_LEFT) / 15 % 4;
				DrawTurnGraph(tempX, tempY, move[drawCount], TRUE);
			}
			else {
				if (drawCount == 60) drawCount = 0;
				DrawTurnGraph(tempX, tempY, wait[drawCount % 4], TRUE);
				drawCount++;
			}
			break;

		case'W':	//����
			if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_LEFT) / 15 % 4;
				DrawTurnGraph(tempX, tempY, move[drawCount], TRUE);
			}
			else {
				if (drawCount == 60) drawCount = 0;
				DrawTurnGraph(tempX, tempY, wait[drawCount % 4], TRUE);
				drawCount++;
			}
			break;
		}
	}
	//DrawFormatString(100, 100, 0xFFFFFF, "%d,%d", tempX, tempY);
	DrawFormatString(100, 80, 0xFFFFFF, "%d,%d", (int)x, (int)y);
}
int Player::getX()
{
	return x;
}
int Player::getY()
{
	return y;
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

	//��ʕ�A�W�����v
	LoadDivGraph("data/img/enemy1JumpP.png", 4, 4, 1, 64, 64, &jump[10]);

}
<<<<<<< HEAD
=======

bool Player::MapHitCheck(int moveX, int moveY)
{
	DrawFormatString(100, 100, 0x00, "%d,%d", ((int)this->y + moveY)/32, ((int)this->x + moveX)/32);
	DrawFormatString(100, 120, 0x00, "%d", vmap[((int)this->y + moveY) / 32][((int)this->x + moveX) / 32]);
	switch (vmap[((int)this->y + moveY) / 32][((int)this->x + moveX) / 32]) {
	case 0:
		return true;
		break;
	case 1:
		if (x > 0) {
			cMove = moveX - ((int)this->x + moveX) % 32;
		}
		else {
			cMove = (int)this->x % 32;
		}
		return false;
		break;
	/*case 2:
		if (moveX > 0)
			cMove = moveX - ((int)this->x + moveX) % 32;
		else
			cMove = (int)this->x % 32;
		return false;
		break;*/
	case 5:
		return true;
		break;
	case 9:
		return true;
		break;
	default:
		return true;
		break;
	}
	return false;
}

void Player::EnemyHitCheck()
{
	//EnemyManeger();
}

>>>>>>> 4c6003a687ec86e208861537b0aa7fee482b198d
