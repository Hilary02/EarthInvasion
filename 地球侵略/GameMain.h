#pragma once
#include "DxLib.h"


/**
�Q�[���V�[���̌Ăяo���̊Ǘ����s���D
��Ђł����Ε����E�݂�����
*/


class GameMain{
public:
	GameMain();
	~GameMain();
	void MainLoop();//�Q�[���S�̗̂���

	enum SCENE { LOGO, TITLE, SELECT, PLAY, OPTION};
	SCENE scene;	//�V�[�����Ƃɋ�ʂ����񋓌^

private:

};

