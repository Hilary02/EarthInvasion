#include "Creature.h"

Creature::Creature(){

	hp = 1;
	attack = 0;
}


Creature::~Creature()
{
}


// ‘Ì—Í‚ğ•ÏX
void Creature::setHp(int newHp){
	hp = newHp;
}


void Creature::modHp(int mod){
	hp += mod;
}

// UŒ‚—Í‚ğİ’è
void Creature::setAtk(int newAtk) {
	attack = newAtk;
}


// ‘Ì—Í‚ğæ“¾‚·‚é‚Æ‚«
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

