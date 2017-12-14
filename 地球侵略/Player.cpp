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
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 1 && !isJumping && !attackFlag)
		liquidFlag = true;
	else if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 0)
		liquidFlag = false;

	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 && !liquidFlag && !attackFlag) {
		isJumping = true;
		jumpPower = -20;
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

	if (MapHitCheck(0, 1)) {
		isJumping = true;
	}
	else {
		isJumping = false;
	}

	if (isJumping) {
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
	DrawFormatString(100, 120, 0xFFFFFF, "Seeing:%d,%d",  ((int)this->x + moveX)/32,((int)this->y + moveY) / 32 );
	//DrawFormatString(100, 120, 0x00, "%d", vmap[((int)this->y + moveY) / 32][((int)this->x + moveX) / 32]);
	switch (vmap[((int)this->y + moveY) / 32+1 ][((int)this->x + moveX) / 32+1] ) {
	case 0:
		return true;
		break;
	case 1:
		DrawFormatString(200, 140, 0xFFFFFF, "見えない壁だ！");
		if (moveX > 0)
			cMove = moveX - ((int)this->x + moveX) % 32;
		else if (moveX < 0)
			cMove = (int)this->x % 32;
		return false;
		break;
	case 2:
		DrawFormatString(200, 140, 0xFFFFFF, "壁だ！");
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
					DrawGraph(tempX, tempY, jump[0], TRUE);
				else if (jumpPower < -1)
					DrawGraph(tempX, tempY, jump[2], TRUE);
			}
			else if (liquidFlag) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4;
				DrawGraph(tempX, tempY, wait[drawCount], TRUE);//仮
			}
			else if (attackFlag) {
				DrawGraph(tempX, tempY, attack[drawCount / 8 % 8], true);
				drawCount++;
				if (drawCount >= 64) attackFlag = false;
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
					DrawTurnGraph(tempX, tempY, jump[0], TRUE);
				else if (jumpPower < -1)
					DrawTurnGraph(tempX, tempY, jump[2], TRUE);
			}
			else if (liquidFlag) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4;
				DrawTurnGraph(tempX, tempY, wait[drawCount], TRUE);//仮
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
	DrawFormatString(100, 100, 0xFFFFFF, "MapChip:%d,%d", (int)(x/32), (int)(y/32));
	if(isJumping) DrawFormatString(300, 80, 0xFFFFFF, "ジャンプ中");
	if (attackFlag) DrawFormatString(300, 100, 0xFFFFFF, "アタック中");
	if (deadFlag) DrawFormatString(300, 120, 0xFFFFFF, "死んだ");

}
int Player::getX()
{
	return x;
}
int Player::getY()
{
	return y;
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
