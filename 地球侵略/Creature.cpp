#include "Creature.h"

Creature::Creature(){

	hp = 1;
	attack = 0;
}


Creature::~Creature()
{
}


// ‘Ì—Í‚ð•ÏX
void Creature::setHp(int newHp){
	hp = newHp;
}


void Creature::modHp(int mod){
	hp += mod;
}

// UŒ‚—Í‚ðÝ’è
void Creature::setAtk() {

}


// ‘Ì—Í‚ðŽæ“¾‚·‚é‚Æ‚«
int Creature::getHp() {
	return this->hp;
}


void Creature::Update(const Collision & playerCol)
{
}

void Creature::Draw(int, int)
{
}

