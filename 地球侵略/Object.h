#pragma once
#include "Root.h"
/**
��������A�C�e���ȂǁC�X�e�[�W��ɔz�u����郂�m���Ǘ�
�ڍז���
*/
class Object :
	public Root {
public:
	Object(int x, int y, char*);
	~Object();
	void Update();
	void Draw();
};

