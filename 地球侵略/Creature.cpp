#include "Creature.h"



Creature::Creature(){
	hp = 1;
	attack = 0;
}


Creature::~Creature()
{
}


// �̗͂�ύX
void Creature::setHp()
{
}


// �U���͂�ݒ�
int Creature::setAtk() {
	return 0;
}


// �̗͂��擾����Ƃ�
int Creature::getHp() {
	return this->hp;
}
