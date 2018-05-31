#pragma once
#include "Object.h"
//#include "IObjectManager.h"

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
	virtual void setHp(int newHp);
	virtual void modHp(int mod);
	// �U���͂�ݒ�(������p��������) byJ
	virtual void setAtk(int newAtk);
	// �̗͂��擾����
	int getHp();

	virtual int update(const Collision & playerCol) override;
	virtual void Draw(int ,int) override;
	//�n�`�Ƃ̓����蔻��ɗp����C���^�[�t�F�[�X
	IObjectManager* IobjMgr;

};

