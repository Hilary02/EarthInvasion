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
	// �̗͂�ύX
	void setHp();
	// �U���͂�ݒ�
	int setAtk();
	// �̗͂��擾����
	int getHp();
};

