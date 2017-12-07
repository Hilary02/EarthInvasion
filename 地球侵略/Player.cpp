#include "DxLib.h"
#include "Player.h"
#include "KeyManager.h"

Player::Player(std::vector<std::vector <int>> const &vmap) {
	this->vmap = vmap;
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

//計算処理
void Player::Update() {
	if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1 && !isAttack) {
		right = false;
		xyCheck = 'x';
		if (MapHitCheck(x - MOVE, y, xyCheck) && MapHitCheck(x - MOVE, y + 63, xyCheck)) {
			x -= MOVE;
		}
		else {
			x -= cMove;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1 && !isAttack) {
		right = true;
		xyCheck = 'x';
		if (MapHitCheck(x + MOVE + 63, y, xyCheck) && MapHitCheck(x + MOVE + 63, y + 63, xyCheck)) {
			x += MOVE;
		}
		else {
			x += cMove;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 1 && !isJumping && !isAttack)
		isLiquid = true;
	else if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 0)
		isLiquid = false;

	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 && !isLiquid && !isAttack) {
		isJumping = true;
		jumpPower = -5;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_A) == 1 && !isAttack) {
		isAttack = true;
		//rect();
		drawCount = 0;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_S) >= 1) {

	}
	if (keyM.GetKeyFrame(KEY_INPUT_E) >= 1) {

	}

	xyCheck = 'y';
	if (MapHitCheck(x, y + 64, xyCheck) && MapHitCheck(x + 63, y + 64, xyCheck)) {
		isJumping = true;
	}
	else if(jumpPower > 0) {
		isJumping = false;
		jumpPower = 0;
	}

	if (isJumping) {
		xyCheck = 'y';
		if (MapHitCheck(x, y + jumpPower + 63, xyCheck) && MapHitCheck(x + 63, y + jumpPower + 63, xyCheck)) {
			y += jumpPower;
			clock++;
			if (clock >= 5) {
				if(jumpPower <= 4)
					jumpPower += 1;
				clock = 0;
			}
		}
		else {
			y += cMove;
		}

	}
	if (hp <= 0) {
		isDead = true;
		//GameOver();
	}

}

bool Player::MapHitCheck(int movedX, int movedY, bool check)
{
	DrawFormatString(100, 120, 0xFFFFFF, "Seeing:%d,%d", movedX / 32, movedY / 32);
	//DrawFormatString(100, 120, 0x00, "%d", vmap[((int)this->y + moveY) / 32][((int)this->x + moveX) / 32]);
	switch (vmap[movedY / 32][movedX / 32]) {
	case 0:
		return true;
		break;
	case 1:
		DrawFormatString(200, 140, 0xFFFFFF, "見えない壁だ！");
		if (check == 'x') {
			if (movedX - x > 0)
				cMove = (movedX - x) - (movedX % 32 + 1);
			else if (movedX - x < 0)
				cMove = x % 32;
		}
		if (check == 'y') {
			if (movedY - (y + 63) > 0) {
				cMove = (movedY - (y + 63)) - (movedY % 32 + 1);
			}
			else if (movedY - y < 0) {
				cMove = y % 32;
			}
		}
		return false;
		break;
	case 2:
		/*
		
		DrawFormatString(200, 140, 0xFFFFFF, "壁だ！");
		if (check == 'x') {
			if (movedX - x > 0)
				cMove = movedX - x - (movedX % 32 + 1);
			else if (movedX - x < 0)
				cMove = x % 32;
		}
		if (check == 'y') {
			if (movedY - (y + 63) > 0) {
				cMove = (movedY - (y + 63)) - (movedY % 32 + 1);
			}
			else if (movedY - y < 0) {
				cMove = y % 32;
			}
		}*/
		
		return false;
		break;
	case 5:
		return true;
		break;
	case 9:
		if (movedY - (y + 63) > 0) {
			cMove = (movedY - (y + 63)) - (movedY % 32 + 1);
		}
		return false;
		break;
	default:
		return true;
		break;
	}
	return false;
}

void Player::Draw(int drawX, int drawY) {
	int tempX = x - drawX;
	int tempY = y - drawY;

	//右向き
	if (right) {
		switch (plState) {

		case 'N':	//主人公
			if (isJumping) {
				if (jumpPower <= 1 && jumpPower >= -1)
					DrawGraph(tempX, tempY, jump[1], TRUE);
				else if (jumpPower > 1)
					DrawGraph(tempX, tempY, jump[2], TRUE);
				else if (jumpPower < -1)
					DrawGraph(tempX, tempY, jump[0], TRUE);
			}
			else if (isLiquid) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4;
				DrawGraph(tempX, tempY, wait[drawCount], TRUE);//仮
			}
			else if (isAttack) {
				DrawGraph(tempX, tempY, attack[drawCount / 8 % 8], true);
				drawCount++;
				if (drawCount >= 64) isAttack = false;
			}
			else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
				DrawGraph(tempX, tempY, move[drawCount], TRUE);
			}
			else {
				if (drawCount > 60) drawCount = 0;
				DrawGraph(tempX, tempY, wait[drawCount / 15 % 4], TRUE);
				drawCount++;
			}
			break;

		case 'A':	//一般兵A
			if (isJumping) {

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

		case'B':	//一般兵B
			if (isJumping) {

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

		case'C':	//一般兵C
			if (isJumping) {

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

		case'W':	//魔女
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
	//左向き
	else if (!right) {
		switch (plState) {

		case 'N':	//主人公
			if (isJumping) {
				if (jumpPower <= 1 && jumpPower >= -1)
					DrawTurnGraph(tempX, tempY, jump[1], TRUE);
				else if (jumpPower > 1)
					DrawTurnGraph(tempX, tempY, jump[2], TRUE);
				else if (jumpPower < -1)
					DrawTurnGraph(tempX, tempY, jump[0], TRUE);
			}
			else if (isLiquid) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4;
				DrawTurnGraph(tempX, tempY, wait[drawCount], TRUE);//仮
			}
			else if (isAttack) {
				DrawTurnGraph(tempX, tempY, attack[drawCount / 8 % 8], true);
				drawCount++;
				if (drawCount >= 64) isAttack = false;
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

		case 'A':	//一般兵A
			if (isJumping) {

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

		case'B':	//一般兵B
			if (isJumping) {

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

		case'C':	//一般兵C
			if (isJumping) {

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

		case'W':	//魔女
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
	DrawFormatString(100, 80, 0xFFFFFF, "Player:%d,%d", (int)x, (int)y);
	DrawFormatString(100, 100, 0xFFFFFF, "MapChip:%d,%d", (int)(x / 32), (int)(y / 32));
	if (isJumping) DrawFormatString(300, 80, 0xFFFFFF, "ジャンプ中");
	if (isAttack) DrawFormatString(300, 100, 0xFFFFFF, "アタック中");
	if (isDead) DrawFormatString(300, 120, 0xFFFFFF, "死んだ");

}
int Player::getX()
{
	return x;
}
int Player::getY()
{
	return y;
}
int Player::getHp()
{
	return this->hp;
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
