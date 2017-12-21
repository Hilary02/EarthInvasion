#include "DxLib.h"
#include "Player.h"
#include "KeyManager.h"

Player::Player(std::vector<std::vector <int>> const &vmap) {
	this->vmap = vmap;
	this->hp = 3;
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
void Player::Update() {
	//状態を見て当たり判定を変更
	PerDecision();
	//キー入力の処理
	if (!isAttack && isMoving == 'N') { //モーション中はキー入力無効
		if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
			right = false;
			xyCheck = 'x';
			if (MapHitCheck(x1 - MOVE, y1, xyCheck) && MapHitCheck(x1 - MOVE, y2, xyCheck) && MapHitCheck(x1 - MOVE, y3, xyCheck)) {
				x -= MOVE;
			}
			else {
				x -= cMove;
			}
		}
		if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
			right = true;
			xyCheck = 'x';
			if (MapHitCheck(x2 + MOVE, y1, xyCheck) && MapHitCheck(x2 + MOVE, y2, xyCheck) && MapHitCheck(x2 + MOVE, y3, xyCheck)) {
				x += MOVE;
			}
			else {
				x += cMove;
			}
		}
		if (!isJumping && !isLiquid) { //ジャンプと液状化してる時に動かない
			if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1) {
				isJumping = true;
				jumpPower = -6;
			}
			if (keyM.GetKeyFrame(KEY_INPUT_A) == 1) {
				isAttack = true;
				drawCount = 0;
			}
			if (plState == 'N') { //ええやん状態のみできる処理
				if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 1) {
					isLiquid = true;
					isMoving = 'L';
					drawCount = 0;
				}
				if (keyM.GetKeyFrame(KEY_INPUT_S) >= 1) {
					if (1) { //ここに死んでる敵がいるか判定
						plState = 'A';
						isMoving = 'I';
						drawCount = 0;
					}
				}
			}
			if (keyM.GetKeyFrame(KEY_INPUT_E) >= 1 && plState != 'N') {
				plState = 'N';
				isMoving = 'O';
				drawCount = 0;
			}
		}
	}
	//液状化解除の処理
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 0 && isLiquid) {
		xyCheck = 'N';
		if (MapHitCheck(x1, y, xyCheck) && MapHitCheck(x2, y, xyCheck) && MapHitCheck(x3, y, xyCheck)) {
			isLiquid = false;
			isMoving = 'R';
			drawCount = 0;
		}
	}
	//通常状態の攻撃判定の処理
	if (isAttack && plState == 'N' && drawCount >= 25 && drawCount <= 32) {
		
	}
	//ジャンプ中の処理
	if (isJumping) {
		xyCheck = 'y';
		if ((MapHitCheck(x1, y2 + jumpPower, xyCheck) && MapHitCheck(x2, y2 + jumpPower, xyCheck) && MapHitCheck(x3, y2 + jumpPower, xyCheck))
		&& (MapHitCheck(x1, y1 + jumpPower, xyCheck) && MapHitCheck(x2, y1 + jumpPower, xyCheck) && MapHitCheck(x3, y1 + jumpPower, xyCheck))) {
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
	if (MapHitCheck(x1, y2 + 1, xyCheck) && MapHitCheck(x2, y2 + 1, xyCheck) && MapHitCheck(x3, y2 + 1, xyCheck)) {
		isJumping = true;
	}
	else if (jumpPower > 0) {
		isJumping = false;
		jumpPower = 0;
	}

	collision->updatePos(x,y);

	if (hp <= 0 && !isDead) {
		isDead = true;
		isMoving = 'D';
		drawCount = 0;
		//GameOver();
	}

	if (invalidDamageTime < 60) invalidDamageTime++;

}

bool Player::MapHitCheck(int movedX, int movedY, char check)
{
	switch (vmap[movedY / 32][movedX / 32]) {
	case 0:
		return true;
		break;
	case 1:
		if (check == 'x') {
			if (movedX - x2 > 0)
				cMove = movedX - x2 - (movedX % 32 + 1);
			else if (movedX - x1 < 0)
				cMove = x1 % 32;
		}
		if (check == 'y') {
			if (movedY - y2 > 0) {
				cMove = (movedY - y2) - (movedY % 32 + 1);
			}
			else if (movedY - y1 < 0) {
				cMove = y1 % 32;
				jumpPower = 0;
			}
		}
		return false;
		break;
	case 2:
		if (check == 'x') {
			if (movedX - x2 > 0)
				cMove = movedX - x2 - (movedX % 32 + 1);
			else if (movedX - x1 < 0)
				cMove = x1 % 32;
		}
		if (check == 'y') {
			if (movedY - y2 > 0) {
				cMove = (movedY - (y+63)) - (movedY % 32 + 1);
			}
			else if (movedY - y1 < 0) {
				cMove = y1 % 32;
				jumpPower = 0;
			}
		}
		
		return false;
		break;
	case 5:
		return true;
		break;
	case 7:
		if (movedY - (y2) > 0) {
			cMove = (movedY - (y2)) - (movedY % 32 + 1);
		}
		return false;
		break;
	case 9:
		if (movedY - (y2) > 0) {
			cMove = (movedY - (y2)) - (movedY % 32 + 1);
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
		else if (isMoving == 'L') {
			MyDraw(tempX, tempY, liquid[drawCount / 5 % 4], right);
			drawCount++;
			if (drawCount >= 20) isMoving = 'N';
		}
		else if (isMoving == 'R') {
			MyDraw(tempX, tempY, liquid[3 - drawCount / 5 % 4], right);
			drawCount++;
			if (drawCount >= 20) isMoving = 'N';
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
				drawCount = keyM.GetKeyFrame(KEY_INPUT_DOWN) / 15 % 4 + 5;
				MyDraw(tempX, tempY, liquid[drawCount], right);
			}
		}
		else if (isAttack) { 
			MyDraw(tempX, tempY, attack[drawCount / 8 % 8], right);
			drawCount++;
			if (drawCount >= 64) isAttack = false;
		}
		else if (isMoving == 'O') {
			MyDraw(tempX, tempY, parasite[drawCount / 8 % 8 + 10], right);
			drawCount++;
			if (drawCount >= 64) isMoving = 'N';
		}
		else if (isMoving == 'D') {
			MyDraw(tempX, tempY, die[drawCount / 8 % 16 ], right);
			if (drawCount <= 128)	drawCount++;
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
			if (jumpPower <= 1 && jumpPower >= -1)
				MyDraw(tempX, tempY, jump[11], !right);
			else if (jumpPower > 1)
				MyDraw(tempX, tempY, jump[12], !right);
			else if (jumpPower < -1)
				MyDraw(tempX, tempY, jump[10], !right);
		}
		else if (isMoving == 'I') {
			MyDraw(tempX, tempY, parasite[drawCount / 8 % 8], right);
			drawCount++;
			if (drawCount >= 64) isMoving = 'N';
		}
		else if (isAttack) {
			MyDraw(tempX, tempY, attack[drawCount / 8 % 8 + 10], !right);
			drawCount++;
			if (drawCount >= 64) isAttack = false;
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
			drawCount = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 8;
			MyDraw(tempX, tempY, move[drawCount+10], !right);
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
			drawCount = keyM.GetKeyFrame(KEY_INPUT_LEFT) / 15 % 8;
			MyDraw(tempX, tempY, move[drawCount+10], !right);
		}
		else {
			if (drawCount > 60) drawCount = 0;
			MyDraw(tempX, tempY, move[drawCount / 15 % 4 + 10], !right);
			drawCount++;
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
	int sizeX1 = 16;
	int sizeX2 = 46;
	int sizeY1 = 23;
	int sizeY2 = 63;
	if (isLiquid) {
		sizeX1 = 3;
		sizeX2 = 57;
		sizeY1 = 48;
		sizeY2 = 63;
	}
	if (plState == 'A' || plState == 'B' || plState == 'C') {
		sizeX1 = 23;
		sizeX2 = 45;
		sizeY1 = 4;
		sizeY2 = 63;
	}
	x1 = x + sizeX1;
	y1 = y + sizeY1;
	x2 = x + sizeX2;
	y2 = y + sizeY2;
	x3 = x + ((sizeX1 + sizeX2) / 2);
	y3 = y + ((sizeY1 + sizeY2) / 2);
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
	//主人公寄生
	LoadDivGraph("data/img/eeyanParasite.png", 8, 4, 2, 64, 64, parasite);
	LoadDivGraph("data/img/eeyanParasiteOut.png", 8, 4, 2, 64, 64, &parasite[10]);
	//主人公死亡
	LoadDivGraph("data/img/eeyanDie.png", 16, 4, 4, 64, 64, die);

	//一般兵Aニュートラル

	//一般兵A歩行
	LoadDivGraph("data/img/enemy1WalkP.png", 8, 4, 2, 64, 64, &move[10]);
	//一般兵Aジャンプ
	LoadDivGraph("data/img/enemy1JumpP.png", 4, 4, 1, 64, 64, &jump[10]);
	//一般兵A攻撃
	LoadDivGraph("data/img/enemy1WaitForAtackP.png", 4, 4, 1, 64, 64, &attack[10]);
	LoadDivGraph("data/img/enemy1AtackP.png", 4, 4, 1, 64, 64, &attack[14]);
	//一般兵A死亡
	LoadDivGraph("data/img/enemy1DieP.png", 8, 4, 2, 64, 64, &die[20]);
}
