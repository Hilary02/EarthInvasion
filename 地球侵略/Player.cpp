#include "DxLib.h"
#include "Player.h"
#include "KeyManager.h"

Player::Player(std::vector<std::vector <int>> const &vmap) {
	this->vmap = vmap;
	this->hp = 15;
	LoadImg();
	collision = new Collision(colXOffset, colYOffset, colXSize, colYSize);
}


//Player::Player(int x, int y) {
//	this->x = x;
//	this->y = y;
//	this->hp = 15;
//	LoadImg();
//}

Player::~Player() {

}

//計算処理
int Player::update() {
	PerDecision();

	if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1 && !isAttack) {
		right = false;
		xyCheck = 'x';
		if (MapHitCheck(x1 - MOVE, y1, xyCheck) && MapHitCheck(x1 - MOVE, y2, xyCheck)) {
			x -= MOVE;
		}
		else {
			x -= cMove;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1 && !isAttack) {
		right = true;
		xyCheck = 'x';
		if (MapHitCheck(x2 + MOVE, y1, xyCheck) && MapHitCheck(x2 + MOVE, y2, xyCheck)) {
			x += MOVE;
		}
		else {
			x += cMove;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 1 && !isJumping && !isAttack && !isLiquid) {
		isLiquid = true;
	}

	else if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 0) {
		xyCheck = 'y';
		if (MapHitCheck(x1, y, xyCheck) && MapHitCheck(x2, y, xyCheck))
			isLiquid = false;
	}

	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 && !isLiquid && !isAttack) {
		isJumping = true;
		jumpPower = -6;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_A) == 1 && !isAttack && !isJumping && !isLiquid) {
		isAttack = true;
		drawCount = 0;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_S) >= 1) {
		//ObjectManager.aaaa(x,y);
	}
	if (keyM.GetKeyFrame(KEY_INPUT_E) >= 1) {

	}

	if (isJumping) {
		xyCheck = 'y';
		if ((MapHitCheck(x1, y2 + jumpPower, xyCheck) && MapHitCheck(x2, y2 + jumpPower, xyCheck))
		&& (MapHitCheck(x1, y1 + jumpPower, xyCheck) && MapHitCheck(x2, y1 + jumpPower, xyCheck))) {
			y += jumpPower;
			clock++;
			if (clock >= 5) {
				if (jumpPower <= 4)
					jumpPower += 1;
				clock = 0;
			}
		}
		else {
			y += cMove;
		}
	}
	else {
		jumpPower = 0;
	}

	xyCheck = 'y';
	if (MapHitCheck(x1, y2 + 1, xyCheck) && MapHitCheck(x2, y2 + 1, xyCheck)) {
		isJumping = true;
	}
	else if (jumpPower > 0) {
		isJumping = false;
		jumpPower = 0;
	}

	collision->updatePos(x,y);

	if (hp <= 0) {
		isDead = true;
		//GameOver();
	}

	if (invalidDamageTime < 60) invalidDamageTime++;
	return 0;
}

bool Player::MapHitCheck(int movedX, int movedY, char check)
{
	switch (vmap[movedY / 32][movedX / 32]) {
	case 0:
		return true;
		break;
	case 1:
		DrawFormatString(200, 140, 0xFFFFFF, "見えない壁だ！");
		if (check == 'x') {
			if (movedX - x > 0)
				cMove = movedX - (x + 63) - (movedX % 32 + 1);
			else if (movedX - x < 0)
				cMove = x % 32;
		}
		if (check == 'y') {
			if (movedY - (y + 63) > 0) {
				cMove = (movedY - (y + 63)) - (movedY % 32 + 1);
			}
			else if (movedY - y < 0) {
				cMove = y % 32;
				jumpPower = 0;
			}
		}
		return false;
		break;
	case 2:
		DrawFormatString(200, 140, 0xFFFFFF, "壁だ！");
		if (check == 'x') {
			if (movedX - x > 0)
				cMove = movedX - (x + 63) - (movedX % 32 + 1);
			else if (movedX - x < 0)
				cMove = x % 32;
		}
		if (check == 'y') {
			if (movedY - (y + 63) > 0) {
				cMove = (movedY - (y + 63)) - (movedY % 32 + 1);
			}
			else if (movedY - y < 0) {
				cMove = y % 32;
				jumpPower = 0;
			}
		}
		
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
	DrawFormatString(0, 0, 0xFFFFFF, "%d", isLiquid);
	
	switch (plState) {
	case 'N':	//主人公
		if (isJumping) {
			if (jumpPower <= 1 && jumpPower >= -1)
				MyDraw(tempX, tempY, jump[1], right);
			else if (jumpPower > 1)
				MyDraw(tempX, tempY, jump[2], right);
			else if (jumpPower < -1)
				MyDraw(tempX, tempY, jump[0], right);
		}
		else if (isLiquid) {
			if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4 + 5;
				MyDraw(tempX, tempY, liquid[drawCount], right);
			}
			else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
				drawCount = keyM.GetKeyFrame(KEY_INPUT_LEFT) / 15 % 4 + 5;
				MyDraw(tempX, tempY, liquid[drawCount], right);
			}
			else {

				if(keyM.GetKeyFrame(KEY_INPUT_DOWN) < 20)
					drawCount = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 5 % 4;

				else 
					drawCount = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4 + 5;
				MyDraw(tempX, tempY, liquid[drawCount], right);
			}
		}
		else if (isAttack) {
			MyDraw(tempX, tempY, attack[drawCount / 8 % 8], right);
			drawCount++;
			if (drawCount >= 64) isAttack = false;
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
			drawCount = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 4;
			MyDraw(tempX, tempY, move[drawCount], right);
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
			drawCount = keyM.GetKeyFrame(KEY_INPUT_LEFT) / 15 % 4;
			MyDraw(tempX, tempY, move[drawCount], right);
		}
		else {
			if (drawCount > 60) drawCount = 0;
			MyDraw(tempX, tempY, wait[drawCount / 15 % 4], right);
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
			DrawGraph(tempX, tempY, wait[drawCount % 4], TRUE);
			drawCount++;
			if (drawCount == 60) drawCount = 0;
		}
		break;
	}


	//DrawFormatString(100, 100, 0xFFFFFF, "%d,%d", tempX, tempY);
	DrawFormatString(100, 80, 0xFFFFFF, "Player:%d,%d", (int)x, (int)y);
	DrawFormatString(100, 100, 0xFFFFFF, "MapChip:%d,%d", (int)(x / 32), (int)(y / 32));
	if (isJumping) DrawFormatString(300, 80, 0xFFFFFF, "ジャンプ中,%d",jumpPower);
	if (isAttack) DrawFormatString(300, 100, 0xFFFFFF, "アタック中");
	if (isDead) DrawFormatString(300, 120, 0xFFFFFF, "死んだ");

}

void Player::MyDraw(int tempX, int tempY, int movement, bool lrFlag) {
	if (lrFlag) {
		DrawGraph(tempX, tempY, movement, TRUE);
	}
	else {
		DrawTurnGraph(tempX, tempY, movement, TRUE);
	}
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
	return hp;
}

void Player::PerDecision()
{
	int sizeX1 = 0;
	int sizeX2 = 63;
	int sizeY1 = 0;
	int sizeY2 = 63;
	if (isLiquid) {
		sizeY1 = 32;
	}
	x1 = x + sizeX1;
	y1 = y + sizeY1;
	x2 = x + sizeX2;
	y2 = y + sizeY2;

}
void Player::modHp(int mod){
	//変化量が負の場合のみ，無敵時間を起動
	if (mod < 0) {
		if (invalidDamageTime == 60) {
			invalidDamageTime = 0;
			hp += mod;
		}
	}
	else {
		//変化量が正なら無敵時間関係なく変更
		hp += mod;
	}
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
	//主人公液状化
	LoadDivGraph("data/img/eeyanEkijouka.png", 4, 4, 1, 64, 64, liquid);
	LoadDivGraph("data/img/eeyanEkijoukaMove.png", 4, 4, 1, 64, 64, &liquid[5]);
	//主人公攻撃
	LoadDivGraph("data/img/eeyanAttack.png", 8, 4, 2, 64, 64, attack);
	//主人公死亡
	LoadDivGraph("data/img/eeyanDie.png", 16, 4, 4, 64, 64, die);

	//一般兵Aジャンプ
	LoadDivGraph("data/img/enemy1JumpP.png", 4, 4, 1, 64, 64, &jump[10]);

}
