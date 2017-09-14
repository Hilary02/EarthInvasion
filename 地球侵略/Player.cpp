#include "Player.h"
#include "WindowData.h"
#include "KeyManager.h"

#define MOVE 1

Player::Player()
{
}

Player::Player(int x,int y){
	this->x = x;
	this->y = y;
	this->hp = 15;

	//画像読み込み
	//主人公ニュートラル
	LoadDivGraph("data/img/eeyanWait.png", 4, 4, 1, 64, 64, wait);
	//主人公歩行
	LoadDivGraph("data/img/eeyanMove.png", 4, 4, 1, 64, 64, move);
	//主人公攻撃
	LoadDivGraph("data/img/eeyanAttack.png", 8, 4, 2, 64, 64, attack);
	//主人公死亡
	LoadDivGraph("data/img/eeyanDie.png", 16, 4, 4, 64, 64, attack);
}

Player::~Player()
{
}

//計算処理
void Player::Update()
{
	if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
		x -= MOVE;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
		x += MOVE;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 1 && !jump)
		liquid = true;
	else if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 0)
		liquid = false;

	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 && !liquid) {
		jump = true;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_A) >= 1) {

	}
	if (keyM.GetKeyFrame(KEY_INPUT_S) >= 1) {

	}
	if (keyM.GetKeyFrame(KEY_INPUT_E) >= 1) {

	}
	
	if (jump) {
	}
	if (hp <= 0) {
		deadFlag = true;
		//GameOver();
	}

}

void Player::Draw(int drawX,int drawY)
{

}

void Player::MapHitCheck()
{
}

void Player::EnemyHitCheck()
{
}

