#include "Creature.h"

Creature::Creature(){

	hp = 1;
	attack = 0;
}


Creature::~Creature()
{
}


// �̗͂�ύX
void Creature::setHp(int newHp){
	hp = newHp;
}


void Creature::modHp(int mod){
	hp += mod;
}

// �U���͂�ݒ�
void Creature::setAtk(int newAtk) {
	attack = newAtk;
}


// �̗͂��擾����Ƃ�
int Creature::getHp() {
	return this->hp;
}


int Creature::update(const Collision & playerCol)
{
	return 0;
}

void Creature::Draw(int, int)
{
}

