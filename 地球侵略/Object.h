#pragma once
#include <DxLib.h>
#include "Collision.h"
#include "ObjectID.h"

//Enemy�Ȃǂ̊Ǘ��p��
enum class state {
	none,
	alive,
	dead,
	respawn,
};

/**
��������A�C�e���ȂǁC�X�e�[�W��ɔz�u����郂�m���Ǘ�
�ڍז���
*/
class Object {
public:
	Object();
	Object(int x, int y, int handle);
	~Object();
	virtual int update(const Collision & playerCol);
	virtual void Draw(int drawX, int drawY);
	//void collisionCheck();

	// �}�b�v�ɂ����Ă̐�΍��W���w�肷��Ƃ��̍��W�ɐݒ�
	void setAbsolutePos(int modX, int modY);
	//�ړ��ʂ�ݒ肷��ƈ����̒l�ړ�����
	void setRelativePos(int modX, int modY);
	ObjectID getId();

	Collision* collision;
	//���̂���private�ɕς���
	state state = state::none;

protected:
	//�����蔻��̑傫��
	int colXOffset = 0;
	int colYOffset = 0;
	int colXSize = 32;
	int colYSize = 64;
	ObjectID id;

	//���W
	int x, y;

	int imgHandle;
};
