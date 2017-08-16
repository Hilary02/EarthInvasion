#pragma once
#include "Root.h"
class Creature :
	public Root
{
public:
	Creature();
	~Creature();
private:
	int hp;
	int attack;
public:
	// ‘Ì—Í‚ğ•ÏX
	void setHp();
	// UŒ‚—Í‚ğİ’è
	int setAtk();
	// ‘Ì—Í‚ğæ“¾‚·‚é
	int getHp();
};

