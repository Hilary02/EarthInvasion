#include "Creature.h"

Creature::Creature(){

	hp = 1;
	attack = 0;
}


Creature::~Creature()
{
}


// 体力を変更
void Creature::setHp(int newHp){
	hp = newHp;
}


void Creature::modHp(int mod){
	hp += mod;
}

// 攻撃力を設定
void Creature::setAtk() {

}


// 体力を取得するとき
int Creature::getHp() {
	return this->hp;
}


void Creature::Update()
{
}

void Creature::Draw(int, int)
{
}

