#pragma once
#include "Object.h"
/**
�G���l���ȂǁC�L�����N�^�[���Ǘ�����D
�̗͂�U���͂ȂǃX�e�[�^�X�Ǘ����ł���悤�ɁD
*/
class Creature :
	public Object {
public:
	Creature();
	~Creature();
protected:
	int hp;
	int attack;
public:
	// �̗͂�ύX
	void setHp();
	// �U���͂�ݒ�
	int setAtk();
	// �̗͂��擾����
	int getHp();
	void Update();
	void Draw();
};

