#pragma once
#include <DxLib.h>
#include "iHitAction.h"
/**
��������A�C�e���ȂǁC�X�e�[�W��ɔz�u����郂�m���Ǘ�
�ڍז���
*/
class Object {
public:
	Object();
	Object(int x, int y, int handle);
	Object(int x, int y, int handle,iHitAction* hit);
	~Object();
	virtual void Update();
	virtual void Draw(int drawX, int drawY);

	// �}�b�v�ɂ����Ă̐�΍��W���w�肷��Ƃ��̍��W�ɐݒ�
	void setAbsolutePos(int modX, int modY);
	//�ړ��ʂ�ݒ肷��ƈ����̒l���ړ������ʒu�ֈړ�
	void setRelativePos(int modX, int modY);

	/*
	�����Ƃ��ēn���ꂽPlayer�ƐڐG������Ƃ�D
	���炩�ƐڐG�����Ƃ���1��Ԃ��C�ڐG���Ȃ������ꍇ��0��Ԃ��D
	����̍ۂɗ��p����l��x,y,
	*/
	virtual int hitCheck(Object* target);
	


	/*
	�����ƐڐG�������Ƃ��Ɏ��s����鏈��
	*/
	void onHit(Object target);

	int x, y;
	int imgHundle;
//	float collisionSize = 0.8;

	iHitAction* HitAction;
};
