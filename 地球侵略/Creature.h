#pragma once
#include "Root.h"
/**
�G���l���ȂǁC�L�����N�^�[���Ǘ�����D
�̗͂�U���͂ȂǃX�e�[�^�X�Ǘ����ł���悤�ɁD
*/
class Creature :
	public Root {
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
	void Update();
	void Draw();
};

