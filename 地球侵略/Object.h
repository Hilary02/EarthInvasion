#pragma once
#include <DxLib.h>
#include "Collision.h"
#include "ICollisionManager.h"
/**
��������A�C�e���ȂǁC�X�e�[�W��ɔz�u����郂�m���Ǘ�
�ڍז���
*/
class Object {
public:
	Object();
	//Object(int x, int y, int handle);
	Object(int x, int y, int handle,ICollisionManager* IcolMgr);
	~Object();
	virtual int update(const Collision & playerCol);
	virtual void Draw(int drawX, int drawY);
	//void collisionCheck();

	// �}�b�v�ɂ����Ă̐�΍��W���w�肷��Ƃ��̍��W�ɐݒ�
	void setAbsolutePos(int modX, int modY);
	//�ړ��ʂ�ݒ肷��ƈ����̒l�ړ�����
	void setRelativePos(int modX, int modY);
	int getId();

	Collision* collision;
protected:
	//�����蔻��̑傫��
	int colXOffset = 0;
	int colYOffset = 0;
	int colXSize = 32;
	int colYSize = 64;
	int id;

	//���W
	int x, y;

	int imgHandle;
	ICollisionManager* IcolMgr;
};
