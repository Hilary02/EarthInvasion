#include "DxLib.h"
#include "Player.h"
#include "KeyManager.h"
#include "ObjectManager.h"
#include "SceneManager.h"

Player::Player(std::vector<std::vector <int>> const &vmap, IObjectManager* Iobj, IStageBase* stage) {
	LoadImg();
	this->Istage = stage;
	this->IobjMgr = Iobj;
	this->vmap = vmap;

	this->hp = 10;
	colXOffset = 16;
	colXSize = 30;
	colYSize = 44;
	colYOffset = 64 - colYSize;
	eeyanCol = new Collision(colXOffset, colYOffset, colXSize, colYSize);
	liquidCol = new Collision(10, 48, 40, 16);
}

Player::~Player() {
	delete eeyanCol;
	delete liquidCol;
	collision = new Collision();	//むりくり
}

int Player::update() {
	//当たり判定に寄生状態を記録
	if (preParasite != 0) {
		collision->playerParasite = preParasite;
		preParasite = 0;
	}

	//寄生判定
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 0 && isLiquid) {
		xyCheck = 'N';
		if (MapHitCheck(x1, y, xyCheck) && MapHitCheck(x2, y, xyCheck) && MapHitCheck(x3, y, xyCheck)) {
			isLiquid = false;
			isMoving = 'R';
			drawCount = 0;
		}
	}

	//液体判定
	if (isLiquid) {
		collision = liquidCol;
	}
	else {
		collision = eeyanCol;
	}
	collision->updatePos(x, y);

	//当たり判定決定
	PerDecision();

	//左右移動
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
				SoundM.Se("data/se/jump.wav");
				jumpPower = -5.1;
				clock = 0;
			}
			if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
				isAttack = true;
				SoundM.Se("data/se/Attack.wav");
				nowAttacking = true;
				drawCount = 0;
			}
			if (plState == playerState::Alien) {
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
									plState = playerState::Soldier;
									isMoving = 'I';
									drawCount = 0;
									preParasite = 1;
									setAtk(ene->getAtk());
								}
								break;
							}
							case ObjectID::soldierB: //ベテラン兵
							{
								Enemy* ene = (Enemy*)o;
								if (ene->getDeadState() == true) {
									plState = playerState::Veteran;
									isMoving = 'I';
									drawCount = 0;
									preParasite = 2;
									setAtk(ene->getAtk());
								}
								break;
							}
							case ObjectID::venomMan: // 毒人間
							{
								Enemy* ene = (Enemy*)o;
								if (ene->getDeadState() == true) {
									plState = playerState::Venom;
									isMoving = 'I';
									drawCount = 0;
									preParasite = 1;
									setAtk(ene->getAtk());
								}
								break;
							}
							case ObjectID::robotEnemy: //ロボット兵士
							{
								Enemy* ene = (Enemy*)o;	//いいのかな？
								if (ene->getDeadState() == true) {
									removeCT = 0;
									plState = playerState::Robot;
									isMoving = 'I';
									drawCount = 0;
									preParasite = 1;
									setAtk(ene->getAtk());
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

			//毒、ロボット特殊寄生状態処理
			if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 45 && plState != playerState::Alien && plState != playerState::Venom) {
				plState = playerState::Alien;
				isMoving = 'O';
				drawCount = 0;
				collision->playerParasite = 0;
			}
			else if (removeCT >= 900 && plState == playerState::Robot) {
				plState = playerState::Alien;
				isMoving = 'O';
				drawCount = 0;
				collision->playerParasite = 0;
			}
			else {
				removeCT++;
			}

		}
	}
	updateCT += 1;
	if (collision->playerState && updateCT > 60)
	{
		collision->playerState = 0;
		updateCT = 0;
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

	collision->updatePos(x, y);


	//毒状態
	if (plState == playerState::Venom) {
		modHp(-1);
	}

	//弾の処理
	for (auto &bull : bullets) {
		bulletindex++;
		if (!bull->isOutOfRange()) {
			bull->setState(-1);
		}
		for (auto o : IobjMgr->getObjectList()) {
			if (bull->collision->doCollisonCheck(o->collision->hitRange)) {
				switch (o->getId()) {
				case ObjectID::soldierA:
				case ObjectID::soldierB:
				case ObjectID::DrG:
				case ObjectID::witch:
				case ObjectID::robotEnemy:
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
	for (auto t : IobjMgr->getObjectList()) {
		if (collision->doCollisonCheck(t->collision->hitRange)) {
			switch (t->getId()) {
			case ObjectID::spark: //ビリビリ
			{
				int leftTX = t->collision->hitRange.xPos + t->collision->hitRange.xOffset;
				int leftPX = collision->hitRange.xPos + collision->hitRange.xOffset;
				int topTY = t->collision->hitRange.yPos + t->collision->hitRange.yOffset;
				int topPY = collision->hitRange.yPos + collision->hitRange.yOffset;


				if (topPY > topTY + 20) {
					//tamesi		//	y = topTY + t->collision->hitRange.ySize - collision->hitRange.yOffset;
					jumpPower = 0;
				}
				else if (leftPX < leftTX) {
					x = leftTX - collision->hitRange.xSize - collision->hitRange.xOffset;
				}
				else if (leftPX > leftTX) {
					x = leftTX + t->collision->hitRange.xSize - collision->hitRange.xOffset;
				}

				isAttack = false;

				break;
			}
			default:
				break;
			}
		}
	}
	collision->updatePos(x, y);

	//通常状態の攻撃処理 
	if (isAttack && plState == playerState::Alien && drawCount >= 25 && drawCount <= 32) {
		if (right)
		{
			collision->updatePos(x + 10, y);
			collision->hitRange.xSize = 80;
		}
		else if (!right)
		{
			collision->updatePos(x - 70, y);
			collision->hitRange.xSize = 60;

		}
		collision->playerState = 1;
	}
	else {
		collision->hitRange.xSize = 32;
		nowAttacking = false;
	}

	//一般兵状態の攻撃処理 
	bulletCT += 1;
	if (isAttack && (plState == playerState::Soldier || plState == playerState::Veteran || plState == playerState::Robot) && drawCount >= 25 && drawCount <= 32)
	{
		if (bulletCT > 60)
		{
			bulletCT = 0;
			Bullet* objBull = new Bullet(x, y, getAtk(), bulletHandle, right, ObjectID::playerBullet);
			bullets.push_back(objBull);
			IobjMgr->addObject(objBull);
		}
	}

	//地形オブジェクトとの当たり判定をとり，位置の修正
	for (auto t : IobjMgr->getTerrainList()) {
		if (collision->doCollisonCheck(t->collision->hitRange)) {
			switch (t->getId()) {
			case ObjectID::lockedDoor: //扉
			{
				if (plState == playerState::Alien && isAttack) {
					//攻撃中は座標移動なし
				}
				else {
					int leftTX = t->collision->hitRange.xPos + t->collision->hitRange.xOffset;
					int leftPX = collision->hitRange.xPos + collision->hitRange.xOffset;

					if (leftPX < leftTX) {
						x = leftTX - collision->hitRange.xSize - collision->hitRange.xOffset;
					}
					else if (leftPX > leftTX) {
						x = leftTX + t->collision->hitRange.xSize - collision->hitRange.xOffset;
					}
				}
				isAttack = false;
				nowAttacking = false;

				break;
			}
			case ObjectID::movingFloor: //動く床
			{
				int topTY = t->collision->hitRange.yPos;
				int underTY = t->collision->hitRange.yPos + t->collision->hitRange.yOffset + t->collision->hitRange.ySize;
				int topPY = collision->hitRange.yPos;
				int underPY = collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize;

				if (underPY <= underTY + 8/*少し吸い込まれる*/) {
					y = topTY - collision->hitRange.yOffset - collision->hitRange.ySize + 2;
					isJumping = false;
				}
			}
			break;
			case ObjectID::alienLaser:
				modHp(-100);
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
			case ObjectID::soldierB:
				if (o->state == State::alive && !(collision->playerState == 1 && !nowAttacking))modHp(-1);
				break;
			case ObjectID::healPot: //回復ポッド
				modHp(5);
				break;
			case ObjectID::detoxPot://毒消し
				plState = playerState::Alien;
				isMoving = 'O';
				drawCount = 0;
				collision->playerParasite = 0;
				break;
			case ObjectID::spike: //とげとげ
				modHp(-1);
				break;
			case ObjectID::abyss:	//奈落。ゲームオーバー
				//isDead = true;
				isMoving = 'D';
				drawCount = 0;
				modHp(-99, true);
				break;
			case ObjectID::enemyBullet: //一般兵の弾
				modHp(-((Bullet*)o)->getAtk());
				break;
			case ObjectID::fire:
				modHp(-1);
				break;
			case ObjectID::alienLaser:
				modHp(-1);
				break;
			case ObjectID::spark: //ビリビリ
			{
				modHp(-1);
				int leftTX = o->collision->hitRange.xPos + o->collision->hitRange.xOffset;
				int leftPX = collision->hitRange.xPos + collision->hitRange.xOffset;
				int topTY = o->collision->hitRange.yPos + o->collision->hitRange.yOffset;
				int topPY = collision->hitRange.yPos + collision->hitRange.yOffset;


				if (topPY > topTY + 20) {
					y = topTY + o->collision->hitRange.ySize - collision->hitRange.yOffset;
					jumpPower = 0;
				}
				else if (leftPX < leftTX) {
					x = leftTX - collision->hitRange.xSize - collision->hitRange.xOffset;
				}
				else if (leftPX > leftTX) {
					x = leftTX + o->collision->hitRange.xSize - collision->hitRange.xOffset;
				}

				isAttack = false;
				break;
			}
			default:
				break;
			}
		}

	}


	if (hp <= 0 && !isDead) {
		SoundM.Se("data/se/death.wav");
		isDead = true;
		isMoving = 'D';
		drawCount = 0;
		//ゲームオーバー処理．ここでやっていいのか？
		//SceneM.ChangeScene(scene::GameOver);
		Istage->PlayAnimation(deadAnime);	//ゲームオーバー演出に入る
	}

	invalidDamageTime++;	//無敵時間

		//寄生解除バー
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 1 && plState != playerState::Alien) {
		if ((1 - (double)keyM.GetKeyFrame(KEY_INPUT_DOWN) / 45) > 0) {
			gauge_length = (1 - (double)keyM.GetKeyFrame(KEY_INPUT_DOWN) / 45);
		}
	}
	else {
		gauge_length = 0;
	}

	return 0;
}

bool Player::MapHitCheck(int movedX, int movedY, char check)
{
	clsDx();
	switch (vmap[movedY / 32][movedX / 32]) {
	case (int)ObjectID::inVisibleWall:
	case (int)ObjectID::ground:
	case (int)ObjectID::colorDifGround:
		if (check == 'x') {
			if (movedX - x2 > 0)
				cMove = movedX - x2 - (movedX % 32 + 1);
			else if (movedX - x1 < 0) {
				if (13 <= x % 32 && x % 32 <= 16 && isLiquid) {	//左移動
					cMove = x1 % 32 - 19;
				}
				else {
					cMove = x1 % 32;			//ここを左右で対応を変えれば行けるはず
				}
			}
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

	//DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);

	int tempX = x - drawX;
	int tempY = y - drawY;

	switch (plState) {
	case playerState::Alien://ええやん状態
		eeyanDrawImg(tempX, tempY);
		break;
	case playerState::Soldier:
	case playerState::Veteran:
	case playerState::Venom:
	case playerState::Robot:
		parasiteDrawImg(tempX, tempY, plState);
		break;
	case playerState::C:	//NOTE:用途不明
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

	case playerState::W:	//NOTE:用途不明
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

	//寄生解除バー
	if (plState != playerState::Alien) {
		DrawExtendGraph(tempX + 16, tempY - 18, tempX + 16 + 50 * gauge_length, tempY - 4, img_gauge, false);
	}
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

void Player::eeyanDrawImg(int tempX, int tempY) {
	//ジャンプの画像が全部使ってない!?
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
}

void Player::parasiteDrawImg(int tempX, int tempY, playerState plstate) {
	paraImg* imgPath;
	switch (plstate) {
	case playerState::Soldier:	imgPath = &soldier;	break;
	case playerState::Veteran:	imgPath = &veteran;	break;
	case playerState::Venom:	imgPath = &venom;	break;
	case playerState::Robot:	imgPath = &robot;	break;
	default:					return;
	}

	if (isJumping) {
		if (jumpPower <= 1 && jumpPower >= -1)
			MyDraw(tempX, tempY, imgPath->jump[1], right);
		else if (jumpPower > 1)
			MyDraw(tempX, tempY, imgPath->jump[2], right);
		else if (jumpPower < -1)
			MyDraw(tempX, tempY, imgPath->jump[0], right);
	}
	else if (isMoving == 'I') {
		MyDraw(tempX, tempY, parasite[drawCount / 8 % 8], right);
		drawCount++;
		if (drawCount >= 64) isMoving = 'N';
	}
	else if (isAttack) {
		if (keyM.GetKeyFrame(KEY_INPUT_LEFT) == 0 && keyM.GetKeyFrame(KEY_INPUT_RIGHT) == 0) {
			MyDraw(tempX, tempY, imgPath->attack[drawCount / 8 % 8], right);
			drawCount++;
			if (drawCount >= 64) isAttack = false;
		}
		else {
			MyDraw(tempX, tempY, imgPath->attack[drawCount / 8 % 4], right);
			drawCount++;
			if (drawCount >= 32) isAttack = false;
		}
	}
	else if (isMoving == 'D') {
		MyDraw(tempX, tempY, imgPath->die[drawCount / 8 % 8], right);
		drawCount++;
		if (drawCount >= 64) isMoving = 'N';
	}
	else if (isDead) {
		MyDraw(tempX, tempY, imgPath->die[7], right);
	}
	else if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
		drawCount = keyM.GetKeyFrame(KEY_INPUT_RIGHT) / 15 % 8;
		MyDraw(tempX, tempY, imgPath->move[drawCount], right);
	}
	else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
		drawCount = keyM.GetKeyFrame(KEY_INPUT_LEFT) / 15 % 8;
		MyDraw(tempX, tempY, imgPath->move[drawCount], right);
	}
	else {
		MyDraw(tempX, tempY, imgPath->wait, right);
	}
}

int Player::getX() { return x; }
int Player::getY() { return y; }
int Player::getHp() { return hp; }
bool Player::getDirection() { return right; }

void Player::PerDecision() {
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
	if (plState == playerState::Soldier || plState == playerState::Veteran || plState == playerState::C || plState == playerState::Robot) {
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
void Player::modHp(int mod, bool through) {
	if (mod < 0) {
		if (through) {
			hp += mod;
		}
		else if (invalidDamageTime >= 120) {
			invalidDamageTime = 0;
			hp += mod;
		}
	}
	else {
		hp += mod;
		if (hp > 16) { hp = 15; }
	}
}

void Player::LoadImg() {
	LoadDivGraph("data/img/eeyanWait.png", 4, 4, 1, 64, 64, wait);
	LoadDivGraph("data/img/eeyanMove.png", 4, 4, 1, 64, 64, move);
	LoadDivGraph("data/img/eeyanJump.png", 4, 4, 1, 64, 64, jump);
	LoadDivGraph("data/img/eeyanEkijouka.png", 4, 4, 1, 64, 64, liquid);
	LoadDivGraph("data/img/eeyanEkijoukaMove.png", 4, 4, 1, 64, 64, &liquid[5]);
	LoadDivGraph("data/img/eeyanAttack.png", 8, 4, 2, 64, 64, attack);
	LoadDivGraph("data/img/eeyanParasite.png", 8, 4, 2, 64, 64, parasite);
	LoadDivGraph("data/img/eeyanParasiteOut.png", 8, 4, 2, 64, 64, &parasite[10]);
	LoadDivGraph("data/img/eeyanDie.png", 16, 4, 4, 64, 64, die);

	soldier.wait = LoadGraph("data/img/enemy1WaitP.png", 0);
	LoadDivGraph("data/img/enemy1WalkP.png", 8, 4, 2, 64, 64, soldier.move);
	LoadDivGraph("data/img/enemy1JumpP.png", 4, 4, 1, 64, 64, soldier.jump);
	LoadDivGraph("data/img/enemy1WaitForAttackP.png", 4, 4, 1, 64, 64, soldier.attack);
	LoadDivGraph("data/img/enemy1AttackP.png", 4, 4, 1, 64, 64, &soldier.attack[4]);
	LoadDivGraph("data/img/enemy1DieP.png", 8, 4, 2, 64, 64, soldier.die);

	veteran.wait = LoadGraph("data/img/enemy3WaitP.png", 0);
	LoadDivGraph("data/img/enemy3WalkP.png", 8, 4, 2, 64, 64, veteran.move);
	LoadDivGraph("data/img/enemy3JumpP.png", 4, 4, 1, 64, 64, veteran.jump);
	LoadDivGraph("data/img/enemy3WaitForAttackP.png", 4, 4, 1, 64, 64, veteran.attack);
	LoadDivGraph("data/img/enemy3AttackP.png", 4, 4, 1, 64, 64, &veteran.attack[4]);
	LoadDivGraph("data/img/enemy3DieP.png", 8, 4, 2, 64, 64, veteran.die);

	robot.wait = LoadGraph("data/img/enemy4WaitP.png", 0);
	LoadDivGraph("data/img/enemy4WalkP.png", 8, 4, 2, 64, 64, robot.move);
	LoadDivGraph("data/img/enemy4JumpP.png", 4, 4, 1, 64, 64, robot.jump);
	LoadDivGraph("data/img/enemy4WaitForAttackP.png", 4, 4, 1, 64, 64, robot.attack);
	LoadDivGraph("data/img/enemy4AttackP.png", 4, 4, 1, 64, 64, &robot.attack[4]);
	LoadDivGraph("data/img/enemy4DieP.png", 8, 4, 2, 64, 64, robot.die);

	venom.wait = LoadGraph("data/img/enemy1WaitPoison.png", 0);
	LoadDivGraph("data/img/enemy1WalkPoison.png", 8, 4, 2, 64, 64, venom.move);
	LoadDivGraph("data/img/enemy1JumpPoison.png", 4, 4, 1, 64, 64, venom.jump);
	LoadDivGraph("data/img/enemy1WaitForAttackPoison.png", 4, 4, 1, 64, 64, venom.attack);
	LoadDivGraph("data/img/enemy1AttackPoison.png", 4, 4, 1, 64, 64, &venom.attack[4]);
	LoadDivGraph("data/img/enemy1DiePoison.png", 8, 4, 2, 64, 64, venom.die);

	img_gauge = LoadGraph("data/img/gauge.png");
}
