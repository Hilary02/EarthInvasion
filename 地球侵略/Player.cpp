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

//vZ
void Player::Update() {
	PerDecision();

	if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1 && !isAttack && isMoving == 'N') {
		right = false;
		xyCheck = 'x';
		if (MapHitCheck(x1 - MOVE, y1, xyCheck) && MapHitCheck(x1 - MOVE, y2, xyCheck) && MapHitCheck(x1 - MOVE, y3, xyCheck)) {
			x -= MOVE;
		}
		else {
			x -= cMove;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1 && !isAttack && isMoving == 'N') {
		right = true;
		xyCheck = 'x';
		if (MapHitCheck(x2 + MOVE, y1, xyCheck) && MapHitCheck(x2 + MOVE, y2, xyCheck) && MapHitCheck(x2 + MOVE, y3, xyCheck)) {
			x += MOVE;
		}
		else {
			x += cMove;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 1 && !isJumping && !isAttack && !isLiquid && isMoving == 'N') {
		isLiquid = true;
		isMoving = 'L';
		drawCount = 0;
	}

	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 0 && isLiquid) {
		xyCheck = 'N';
		if (MapHitCheck(x1, y, xyCheck) && MapHitCheck(x2, y, xyCheck) && MapHitCheck(x3, y, xyCheck)) {
			isLiquid = false;
			isMoving = 'R';
		}
	}

	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 && !isLiquid && !isAttack && isMoving == 'N' && !isJumping) {
		isJumping = true;
		jumpPower = -6;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_A) == 1 && !isAttack && !isJumping && !isLiquid && isMoving == 'N') {
		isAttack = true;
		drawCount = 0;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_S) >= 1 && !isAttack && !isJumping && !isLiquid && isMoving == 'N') {
		if (1) {
			isMoving = 'I';
			drawCount = 0;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_E) >= 1 && !isAttack && !isJumping && !isLiquid && isMoving == 'N') {
		if (plState != 'N') {
			isMoving = 'O';
			drawCount = 0;
		}
	}

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

	if (hp <= 0) {
		isDead = true;
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
		DrawFormatString(200, 140, 0xFFFFFF, "ĮūI");
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
	DrawFormatString(0, 0, 0xFFFFFF, "%d", isLiquid);
	
	switch (plState) {
	case 'N':	//ålö
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
		else if (isMoving == 'I') {
			MyDraw(tempX, tempY, parasite[drawCount / 8 % 8], right);
			drawCount++;
			if (drawCount >= 64) isMoving = 'N';
		}
		else if (isMoving == 'O') {
			MyDraw(tempX, tempY, parasite[drawCount / 8 % 8 + 10], right);
			drawCount++;
			if (drawCount >= 64) isMoving = 'N';
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

	case 'A':	//ęĘšA
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

	case'B':	//ęĘšB
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

	case'C':	//ęĘšC
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

	case'W':	//
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
	if (isJumping) DrawFormatString(300, 80, 0xFFFFFF, "Wv,%d",jumpPower);
	if (isAttack) DrawFormatString(300, 100, 0xFFFFFF, "A^bN");
	if (isDead) DrawFormatString(300, 120, 0xFFFFFF, "ņū");

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
		sizeY1 = 32;
	}
	x1 = x + sizeX1;
	y1 = y + sizeY1;
	x2 = x + sizeX2;
	y2 = y + sizeY2;
	x3 = x + ((sizeX1 + sizeX2) / 2);
	y3 = y + ((sizeY1 + sizeY2) / 2);
}
void Player::modHp(int mod){
	//ÏŧĘŠĖęĖÝCģGÔðNŪ
	if (mod < 0) {
		if (invalidDamageTime == 60) {
			invalidDamageTime = 0;
			hp += mod;
		}
	}
	else {
		//ÏŧĘŠģČįģGÔÖWČ­ÏX
		hp += mod;
	}
}
//æĮÝÝ
void Player::LoadImg()
{
	//ålöj[g
	LoadDivGraph("data/img/eeyanWait.png", 4, 4, 1, 64, 64, wait);
	//ålöās
	LoadDivGraph("data/img/eeyanMove.png", 4, 4, 1, 64, 64, move);
	//ålöWv
	LoadDivGraph("data/img/eeyanJump.png", 4, 4, 1, 64, 64, jump);
	//ålötóŧ
	LoadDivGraph("data/img/eeyanEkijouka.png", 4, 4, 1, 64, 64, liquid);
	LoadDivGraph("data/img/eeyanEkijoukaMove.png", 4, 4, 1, 64, 64, &liquid[5]);
	//ålöU
	LoadDivGraph("data/img/eeyanAttack.png", 8, 4, 2, 64, 64, attack);
	//ålöņķ
	LoadDivGraph("data/img/eeyanParasite.png", 8, 4, 2, 64, 64, parasite);
	LoadDivGraph("data/img/eeyanParasiteOut.png", 8, 4, 2, 64, 64, &parasite[10]);
	//ålöS
	LoadDivGraph("data/img/eeyanDie.png", 16, 4, 4, 64, 64, die);

	//ęĘšAj[g

	//ęĘšAās
	LoadDivGraph("data/img/enemy1WalkP.png", 8, 4, 2, 64, 64, &move[10]);
	//ęĘšAWv
	LoadDivGraph("data/img/enemy1JumpP.png", 4, 4, 1, 64, 64, &jump[10]);
	//ęĘšAU
	LoadDivGraph("data/img/enemy1WaitForAtackP.png", 4, 4, 1, 64, 64, &attack[10]);
	LoadDivGraph("data/img/enemy1AtackP.png", 4, 4, 1, 64, 64, &attack[15]);
	//ęĘšAS
	LoadDivGraph("data/img/enemy1DieP.png", 8, 4, 2, 64, 64, &die[10]);
}
