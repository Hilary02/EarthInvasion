#include "DrG.h"
#include "Bullet.h"

DrG::DrG() {}

DrG::~DrG() {}

DrG::DrG(int x, int y, int img, ObjectID id, IObjectManager * Iobj, int stageID, IStageBase* stage) {
	this->IobjMgr = Iobj;
	this->x = x;
	this->y = y;
	this->imgHandle = img;
	this->id = id;
	setHp(5);
	LoadDivGraph("data/img/DrG/enemy5Wait.png", 2, 2, 1, 64, 64, img_wait);
	img_damage = LoadGraph("data/img/DrG/enemy5Damage.png");
	LoadDivGraph("data/img/DrG/enemy5Die.png", 4, 4, 1, 64, 64, img_die);
	collision = new Collision(20, 16, 20, 48);
	state = State::alive;

	this->stageId = stageID;
	this->Istage = stage;
}

int DrG::update(const Collision & playerCol) {
	collision->updatePos(x, y);
	counter++;
	invulnerable--;
	//オブジェクトとの当たり判定
	for (auto o : IobjMgr->getObjectList()) {
		switch (o->getId()) {
		case ObjectID::playerBullet: //プレイヤーの弾
			if (collision->doCollisonCheck(o->collision->hitRange)) { //当たり判定をとる
				if (state == State::alive && invulnerable <= 0) {
					modHp(-1);
					invulnerable = invulnerableTime;
				}
			}
			break;
		default:
			break;
		}
	}
	if (state == State::alive && hp <= 0) {
		state = State::dead;
	}
	if (state == State::dead && deadcounter < 79) {
		deadcounter++;
	}

	//表示画像の変更
	imgHandle = img_wait[0];
	if (state == State::alive) {
		if (invulnerable >= 0) {
			imgHandle = img_damage;
		}
		else if ((counter / 25) % 2 == 0) {
			imgHandle = img_wait[0];
		}
		else {
			imgHandle = img_wait[1];
		}
	}
	else if (state == State::dead) {
		imgHandle = img_die[deadcounter / 20];
	}

	if (hp <= 0) {
		//めちゃくちゃ
		savedata.setClearFlag(stageId, 1);
		savedata.save();
		Istage->PlayAnimation(clearAnime);	//クリア演出に入る
	}



	return 0;
}

void DrG::Draw(int drawX, int drawY) {
	//DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);
	if (invulnerable > 0 && (invulnerable / 20) % 2 > 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 170);
	}
	DrawGraph(x - drawX, y - drawY, imgHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
