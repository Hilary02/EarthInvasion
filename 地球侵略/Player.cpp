#include "DxLib.h"
#include "Player.h"
#include "KeyManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"

Player::Player(std::vector<std::vector <int>> const &vmap, IObjectManager* Iobj) {
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

int Player::update() {
	debugMode();
	PerDecision();
	if (!isAttack && !isDead && isMoving == 'N') {
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
		if (!isJumping && !isLiquid) {
			if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1) {
				isJumping = true;
				jumpPower = -6;
			}
			if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
				isAttack = true;
				drawCount = 0;
			}
			if (plState == 'N') {
				if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 1) {
					isLiquid = true;
					isMoving = 'L';
					drawCount = 0;
				}

				/*NOTE:親クラスで定義した変数を子が同名で再定義してしまうと
				親クラスのポインタ型からアクセスしたときに参照エラーが発生する．
				デバッガでみて初めて気が付いた				*/
				//寄生キー
				if (keyM.GetKeyFrame(KEY_INPUT_X) >= 1) {
					for (auto o : IobjMgr->getObjectList()) {
						if (collision->doCollisonCheck(o->collision->hitRange)) { //当たり判定をとる

							switch (o->getId()) {
							case ObjectID::soldierA: //兵士
							{
								Enemy* ene = (Enemy*)o;	//いいのかな？
								if (ene->getDeadState() == true) {
									plState = 'A';
									isMoving = 'I';
									drawCount = 0;
									collision->playerParasite = 1; //当たり判定に寄生状態を記録
								}
								break;
							}
							default:
								break;
							}
						}
					}
				}
			}

			//寄生解除
			if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 45 && plState != 'N') {
				plState = 'N';
				isMoving = 'O';
				drawCount = 0;
				collision->playerParasite = 0;
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
	//collision->updatePos(x, y);

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

	collision->updatePos(x, y);

	//通常状態の攻撃処理 
	if (isAttack && plState == 'N' && drawCount >= 25 && drawCount <= 32) {
		collision->playerState = 1;
		if (right)
		{
			collision->updatePos(x, y);
			collision->hitRange.xSize = 100;
		}
		else if (!right)
		{
			collision->updatePos(x - 70, y);
			collision->hitRange.xSize = 100;

		}
	}
	else {
		collision->hitRange.xSize = 32;
	}

	//一般兵状態の攻撃処理 
	bulletCT += 1;
	if (isAttack && plState == 'A' && drawCount >= 25 && drawCount <= 32)
	{
		if (bulletCT > 60)
		{
			bulletCT = 0;
			Bullet* objBull = new Bullet(x, y, bulletHandle, right, ObjectID::playerBullet);
			bullets.push_back(objBull);
			IobjMgr->addObject(objBull);
		}
	}

	//弾の処理
	for (auto &bull : bullets)
	{
		bulletindex++;
		if (!bull->isOutOfRange())
		{
			bullets.erase(bullets.begin() + bulletindex);
		}

		for (auto o : IobjMgr->getObjectList())
		{
			if (bull->collision->doCollisonCheck(o->collision->hitRange))
			{
				switch (o->getId())
				{
				case ObjectID::soldierA:
					if (o->state == State::alive)bull->setState(-1);
					break;
				default:
					break;
				}
			}
		}
	}
	bulletindex = -1;

	//地形オブジェクトとの当たり判定をとり，位置の修正
	for (auto t : IobjMgr->getTerrainList()) {
		if (collision->doCollisonCheck(t->collision->hitRange)) {
			switch (t->getId()) {
			case ObjectID::lockedDoor: //扉
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
			case ObjectID::moveingFloor: //動く床
			{
				int topTY = t->collision->hitRange.yPos + t->collision->hitRange.yOffset;
				int underTY = t->collision->hitRange.yPos + t->collision->hitRange.yOffset + t->collision->hitRange.ySize;
				int topPY = collision->hitRange.yPos + collision->hitRange.yOffset;
				int underPY = collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize;


				if (underPY <= underTY + 8/*少し吸い込まれる*/) {
					y = topTY - collision->hitRange.ySize + 2;
					isJumping = false;
				}
			}
			break;

			default:
				break;
			}
		}
	}

	//オブジェクトとの当たり判定をとり，プレイヤー自身に影響する処理を行う
	for (auto o : IobjMgr->getObjectList()) {
		if (collision->doCollisonCheck(o->collision->hitRange)) { //当たり判定をとる
			switch (o->getId()) {
			case ObjectID::soldierA: //兵士
				if (o->state == State::alive && !(collision->playerState == 1))modHp(-1);
				break;
			case ObjectID::healPot: //回復ポッド
				modHp(5);
				break;
			case ObjectID::spike: //とげとげ
				modHp(-1);
				break;
			case ObjectID::spark:
				modHp(-1);
				break;
			case ObjectID::enemyBullet: //一般兵の弾
				modHp(-3);
				break;
			case ObjectID::fire:
				modHp(-1);
				break;
			default:
				break;
			}
		}

	}

	updateCT += 1;
	if (collision->playerState && updateCT > 60)
	{
		collision->playerState = 0;
		updateCT = 0;
	}

	if (hp <= 0 && !isDead) {
		isDead = true;
		isMoving = 'D';
		drawCount = 0;
		//ゲームオーバー処理．ここでやっていいのか？
		SceneM.ChangeScene(scene::GameOver);
	}

	invalidDamageTime++;	//無敵時間
	return 0;
}

bool Player::MapHitCheck(int movedX, int movedY, char check)
{
	switch (vmap[movedY / 32][movedX / 32]) {
	case 0:
		return true;
		break;
	case (int)ObjectID::inVisibleWall:
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
	case (int)ObjectID::ground:
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
	case (int)ObjectID::colorDifGround:
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
	case (int)ObjectID::spike:
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

	case 'A':
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

	case'B':
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

	case'C':
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

	case'W':
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
	//修正要素

	if (invalidDamageTime < 120 && (invalidDamageTime / 20) % 2 > 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 170);
		if (lrFlag) {
			DrawGraph(tempX, tempY, movement, TRUE);
		}
		else {
			DrawTurnGraph(tempX, tempY, movement, TRUE);
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	else {
		if (lrFlag) {
			DrawGraph(tempX, tempY, movement, TRUE);
		}
		else {
			DrawTurnGraph(tempX, tempY, movement, TRUE);
		}
	}
}

void Player::debugMode() {
	if (keyM.GetKeyFrame(KEY_INPUT_K) == 1) {
		hp = 0;
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

//体力の変更 ダメージを受けるときだけ120フレームの無敵時間
void Player::modHp(int mod) {
	if (mod < 0) {
		if (invalidDamageTime >= 120) {
			invalidDamageTime = 0;
			hp += mod;
		}
	}
	else {
		hp += mod;
	}
}

void Player::LoadImg()
{

	LoadDivGraph("data/img/eeyanWait.png", 4, 4, 1, 64, 64, wait);
	LoadDivGraph("data/img/eeyanMove.png", 4, 4, 1, 64, 64, move);
	LoadDivGraph("data/img/eeyanJump.png", 4, 4, 1, 64, 64, jump);
	LoadDivGraph("data/img/eeyanEkijouka.png", 4, 4, 1, 64, 64, liquid);
	LoadDivGraph("data/img/eeyanEkijoukaMove.png", 4, 4, 1, 64, 64, &liquid[5]);
	LoadDivGraph("data/img/eeyanAttack.png", 8, 4, 2, 64, 64, attack);
	LoadDivGraph("data/img/eeyanParasite.png", 8, 4, 2, 64, 64, parasite);
	LoadDivGraph("data/img/eeyanParasiteOut.png", 8, 4, 2, 64, 64, &parasite[10]);
	LoadDivGraph("data/img/eeyanDie.png", 16, 4, 4, 64, 64, die);

	LoadDivGraph("data/img/enemy1WaitP.png", 1, 1, 1, 64, 64, &wait[10]);
	LoadDivGraph("data/img/enemy1WalkP.png", 8, 4, 2, 64, 64, &move[10]);
	LoadDivGraph("data/img/enemy1JumpP.png", 4, 4, 1, 64, 64, &jump[10]);
	LoadDivGraph("data/img/enemy1WaitForAtackP.png", 4, 4, 1, 64, 64, &attack[10]);
	LoadDivGraph("data/img/enemy1AtackP.png", 4, 4, 1, 64, 64, &attack[14]);
	LoadDivGraph("data/img/enemy1DieP.png", 8, 4, 2, 64, 64, &die[20]);
}
