#include "DxLib.h"
#include "Player.h"
#include "KeyManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"

Player::Player(std::vector<std::vector <int>> const &vmap,IObjectManager* Iobj) {
	LoadImg();
	this->IobjMgr = Iobj;
	this->vmap = vmap;

	this->hp = 10;
	colXOffset = 16;
	colXSize = 30;
	collision = new Collision(colXOffset, colYOffset, colXSize, colYSize);
}

Player::~Player() {
}

//?v?Z????

int Player::update() {

	PerDecision();
	//?L?[???͂̏???
	if (!isAttack && !isDead && isMoving == 'N') { //???[?V???????Ǝ??S???̓L?[???͖???
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
		if (!isJumping && !isLiquid) { //?W?????v?Ɖt?󉻂??Ă鎞?ɓ????Ȃ?
			if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1) {
				isJumping = true;
				jumpPower = -6;
			}
			if (keyM.GetKeyFrame(KEY_INPUT_A) == 1) {
				isAttack = true;
				drawCount = 0;
			}
			if (plState == 'N') { //?????????݂̂ł??鏈??
				if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 1) {
					isLiquid = true;
					isMoving = 'L';
					drawCount = 0;
				}
				if (keyM.GetKeyFrame(KEY_INPUT_S) >= 1) {
					if (1) { //?????Ɏ??????????邩????
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
	//?t?󉻉???̏???
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 0 && isLiquid) {
		xyCheck = 'N';
		if (MapHitCheck(x1, y, xyCheck) && MapHitCheck(x2, y, xyCheck) && MapHitCheck(x3, y, xyCheck)) {
			isLiquid = false;
			isMoving = 'R';
			drawCount = 0;
		}
	}
	//?ʏ??Ԃ̍U??????????
	if (isAttack && plState == 'N' && drawCount >= 25 && drawCount <= 32) {

	}
	//?W?????v???̏???
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

	if (keyM.GetKeyFrame(KEY_INPUT_W) == 1) {
		collision->playerParasite = 0; //攻撃状態かどうかとか記録
		printfDx("Mode:0");
	}
	if (keyM.GetKeyFrame(KEY_INPUT_E) == 1) {
		collision->playerParasite = 1; //攻撃状態かどうかとか記録
		printfDx("Mode:1");
	}



	collision->updatePos(x, y);
	//collision->playerParasite = 0;//仮なのでいつか統一した規格に
	collision->playerState = 0; //攻撃状態かどうかとか記録



	/*
			めちゃくちゃやん

	*/
//	for (auto t : ObjectManager::terrain) {
	for (auto t : IobjMgr->getTerrainList()) {

		if (collision->doCollisonCheck(t->collision->hitRange)) {
			//int tx = t->collision->hitRange.xPos + t->collision->hitRange.xOffset;

			switch (t->getId()) {
			case 6: //扉
			{
				int leftTX = t->collision->hitRange.xPos + t->collision->hitRange.xOffset;
				int leftPX = collision->hitRange.xPos + collision->hitRange.xOffset;

				if (leftPX < leftTX) {
					x = leftTX - collision->hitRange.xSize - collision->hitRange.xOffset;
				}
				else if (leftPX > leftTX) {
					x = leftTX + t->collision->hitRange.xSize - collision->hitRange.xOffset;
				}
				isAttack = false;

				break;
			}
			case 8: //動く床
			{
				int topTY = t->collision->hitRange.yPos + t->collision->hitRange.yOffset;
				int underTY = t->collision->hitRange.yPos + t->collision->hitRange.yOffset + t->collision->hitRange.ySize;
				int topPY = collision->hitRange.yPos + collision->hitRange.yOffset;
				int underPY = collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize;


				if (underPY <= underTY + 8/*少し吸い込まれる*/) {
					y = topTY - collision->hitRange.ySize + 2;
					//jumpPower = 0;
					isJumping = false;
				}
			}
			break;

			default:
				break;
			}
		}
	}

	if (hp <= 0 && !isDead) {
		isDead = true;
		isMoving = 'D';
		drawCount = 0;
		//ゲームオーバー処理．ここでやっていいのか？
		SceneM.ChangeScene(scene::GameOver);
	}

	if (invalidDamageTime < 60) invalidDamageTime++;	//無敵時間
	return 0;
}

bool Player::MapHitCheck(int movedX, int movedY, char check)
{
	switch (vmap[movedY / 32][movedX / 32]) {
	case 0:
		return true;
		break;
	case 1:

		//d		DrawFormatString(200, 140, 0xFFFFFF, "?????Ȃ??ǂ??I");

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

		//d	DrawFormatString(200, 140, 0xFFFFFF, "?ǂ??I");

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
	case 5:
		return true;
		break;
	case 7:
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
	case 8:
		return true;
		break;
	case 9:
		if (movedY - y2 > 0) {
			cMove = (movedY - y2) - (movedY % 32 + 1);
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
	DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);

	int tempX = x - drawX;
	int tempY = y - drawY;

	switch (plState) {
	case 'N':	//????
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
			MyDraw(tempX, tempY, die[drawCount / 8 % 16], right);
			drawCount++;
			if (drawCount >= 128) isMoving = 'N';
		}
		else if (isDead) {
			MyDraw(tempX, tempY, die[15], right);
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

	case 'A':	//????A
		if (isJumping) {
			if (jumpPower <= 1 && jumpPower >= -1)
				MyDraw(tempX, tempY, jump[11], right);
			else if (jumpPower > 1)
				MyDraw(tempX, tempY, jump[12], right);
			else if (jumpPower < -1)
				MyDraw(tempX, tempY, jump[10], right);
		}
		else if (isMoving == 'I') {
			MyDraw(tempX, tempY, parasite[drawCount / 8 % 8], right);
			drawCount++;
			if (drawCount >= 64) isMoving = 'N';
		}
		else if (isAttack) {
			if (keyM.GetKeyFrame(KEY_INPUT_LEFT) == 0 && keyM.GetKeyFrame(KEY_INPUT_RIGHT) == 0) {
				MyDraw(tempX, tempY, attack[drawCount / 8 % 8 + 10], right);
				drawCount++;
				if (drawCount >= 64) isAttack = false;
			}
			else {
				MyDraw(tempX, tempY, attack[drawCount / 8 % 4 + 14], right);
				drawCount++;
				if (drawCount >= 32) isAttack = false;
			}

		}
		else if (isMoving == 'D') {
			MyDraw(tempX, tempY, die[drawCount / 8 % 8 + 20], right);
			drawCount++;
			if (drawCount >= 64) isMoving = 'N';
		}
		else if (isDead) {
			MyDraw(tempX, tempY, die[27], right);
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
			drawCount = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 8;
			MyDraw(tempX, tempY, move[drawCount + 10], right);
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
			drawCount = keyM.GetKeyFrame(KEY_INPUT_LEFT) / 15 % 8;
			MyDraw(tempX, tempY, move[drawCount + 10], right);
		}
		else {
			MyDraw(tempX, tempY, wait[10], right);
		}
		break;

	case'B':	//????B
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

	case'C':	//????C
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

	case'W':	//????
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


	// DrawFormatString(100, 100, 0xFFFFFF, "%d,%d", tempX, tempY);
	//d	DrawFormatString(100, 80, 0xFFFFFF, "Player:%d,%d", (int)x, (int)y);
	//d DrawFormatString(100, 100, 0xFFFFFF, "MapChip:%d,%d", (int)(x / 32), (int)(y / 32));
	//d if (isJumping) DrawFormatString(300, 80, 0xFFFFFF, "?W?????v??,%d",jumpPower);
	//d if (isAttack) DrawFormatString(300, 100, 0xFFFFFF, "?A?^?b?N??");
	//d if (isDead) DrawFormatString(300, 120, 0xFFFFFF, "????);

}

void Player::MyDraw(int tempX, int tempY, int movement, bool lrFlag) {
	if (lrFlag) {
		DrawGraph(tempX, tempY, movement, TRUE);
	}
	else {
		DrawTurnGraph(tempX, tempY, movement, TRUE);
	}
}

int Player::getX() { return x; }
int Player::getY() { return y; }
int Player::getHp() { return hp; }

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
void Player::modHp(int mod) {
	//?ω??ʂ????̏ꍇ?̂݁C???G???Ԃ?N??
	if (mod < 0) {
		if (invalidDamageTime == 60) {
			invalidDamageTime = 0;
			hp += mod;
		}
	}
	else {
		//?ω??ʂ????Ȃ疳?G???Ԋ֌W?Ȃ??ύX
		hp += mod;
	}
}
//?摜?ǂݍ???
void Player::LoadImg()
{
	//?????j???[?g????
	LoadDivGraph("data/img/eeyanWait.png", 4, 4, 1, 64, 64, wait);
	//??????s
	LoadDivGraph("data/img/eeyanMove.png", 4, 4, 1, 64, 64, move);
	//?????W?????v
	LoadDivGraph("data/img/eeyanJump.png", 4, 4, 1, 64, 64, jump);
	//?????t??
	LoadDivGraph("data/img/eeyanEkijouka.png", 4, 4, 1, 64, 64, liquid);
	LoadDivGraph("data/img/eeyanEkijoukaMove.png", 4, 4, 1, 64, 64, &liquid[5]);
	//?????U??
	LoadDivGraph("data/img/eeyanAttack.png", 8, 4, 2, 64, 64, attack);
	//??????
	LoadDivGraph("data/img/eeyanParasite.png", 8, 4, 2, 64, 64, parasite);
	LoadDivGraph("data/img/eeyanParasiteOut.png", 8, 4, 2, 64, 64, &parasite[10]);
	//???????S
	LoadDivGraph("data/img/eeyanDie.png", 16, 4, 4, 64, 64, die);

	//????A?j???[?g????
	LoadDivGraph("data/img/enemy1WaitP.png", 1, 1, 1, 64, 64, &wait[10]);
	//????A??s
	LoadDivGraph("data/img/enemy1WalkP.png", 8, 4, 2, 64, 64, &move[10]);
	//????A?W?????v
	LoadDivGraph("data/img/enemy1JumpP.png", 4, 4, 1, 64, 64, &jump[10]);
	//????A?U??
	LoadDivGraph("data/img/enemy1WaitForAtackP.png", 4, 4, 1, 64, 64, &attack[10]);
	LoadDivGraph("data/img/enemy1AtackP.png", 4, 4, 1, 64, 64, &attack[14]);
	//????A???S
	LoadDivGraph("data/img/enemy1DieP.png", 8, 4, 2, 64, 64, &die[20]);
}
