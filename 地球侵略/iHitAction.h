#pragma once
class iHitAction
{
//private:
//	virtual ~iHitAction() {}
public:
	virtual int doHitAction(int id) = 0;
};

// �C���^�t�F�[�X���擾����֐�
//iHitAction* GetHitAction(int n);