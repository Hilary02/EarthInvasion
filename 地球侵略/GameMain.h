#pragma once
#include "DxLib.h"

#include "StageSample.h"



class GameMain{
public:
	GameMain();
	~GameMain();
	void MainLoop();//�Q�[���S�̗̂���

	enum SCENE { LOGO, TITLE, CHOICE, PLAY, OPTION};
	SCENE scene;	//�V�[�����Ƃɋ�ʂ����񋓌^

private:

};

