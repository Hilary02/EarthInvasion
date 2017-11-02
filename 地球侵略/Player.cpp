#include "DxLib.h"
#include "Player.h"
#include "KeyManager.h"

Player::Player(std::vector<std::vector <int>> const &vmap):vmap(vmap) {
}

Player::Player(int x, int y) {
	this->x = x;
	this->y = y;
	this->hp = 15;
	LoadImg();
}

Player::~Player() {

}

//計算処理
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

	//右向き
	if (right) {
		switch (plState) {
			
		case 'N':	//主人公
			if (jumpFlag) {
			}
			else if (liquidFlag) {
				i = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);//仮
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
			
		case 'A':	//一般兵A
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
			
		case'B':	//一般兵B
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
			
		case'C':	//一般兵C
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
			
		case'W':	//魔女
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
	//左向き
	else {
		switch (plState) {
			
		case 'N':	//主人公
			if (jumpFlag) {
			}
			else if (liquidFlag) {
				i = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4;
				DrawGraph(tempX, tempY, move[i], TRUE);//仮
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
			
		case 'A':	//一般兵A
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
			
		case'B':	//一般兵B
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
			
		case'C':	//一般兵C
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
			
		case'W':	//魔女
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
	DrawFormatString(100, 80, 0xFFFFFF, "%d,%d", (int)x, (int)y);
}
//画像読み込み
void Player::LoadImg()
{
	//主人公ニュートラル
	LoadDivGraph("data/img/eeyanWait.png", 4, 4, 1, 64, 64, wait);
	//主人公歩行
	LoadDivGraph("data/img/eeyanMove.png", 4, 4, 1, 64, 64, move);
	//主人公ジャンプ
	LoadDivGraph("data/img/eeyanJump.png", 4, 4, 1, 64, 64, jump);
	//主人公攻撃
	LoadDivGraph("data/img/eeyanAttack.png", 8, 4, 2, 64, 64, attack);
	//主人公死亡
	LoadDivGraph("data/img/eeyanDie.png", 16, 4, 4, 64, 64, die);

	//一般兵Aジャンプ
	LoadDivGraph("data/img/enemy1JumpP.png", 4, 4, 1, 64, 64, &jump[10]);

}

bool Player::MapHitCheck(int moveX, int moveY)
{
	switch (vmap[(this->y + moveY) / 32][(this->x + moveX) / 32]) {
	case 0:
		return true;
		break;
	case 1:
		if (x > 0)
			cMove = moveX - ((int)this->x + moveX) % 32;
		else
			cMove = (int)this->x % 32;
		return false;
		break;
	case 2:
		if (x > 0)
			cMove = moveX - ((int)this->x + moveX) % 32;
		else
			cMove = (int)this->x % 32;
		return false;
		break;
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

