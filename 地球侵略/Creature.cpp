#include "Creature.h"



Creature::Creature(){
	hp = 1;
	attack = 0;
}


Creature::~Creature()
{
}


// 体力を変更
void Creature::setHp()
{
}


// 攻撃力を設定
int Creature::setAtk() {
	return 0;
}


// 体力を取得するとき
int Creature::getHp() {
	return this->hp;
}
