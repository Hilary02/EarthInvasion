#include "GameMain.h"
#include "KeyManager.h"
#include "FPS.h"

#include "StageSample.h"
#include "Option.h"

//���݂͕\���������N���X�������œǂ݂���ł��܂��Ă��邪�C�|�C���^��p���ĕK�v�������ǂ݂��߂�悤��
int time = 0;
StageSample stage1;
Option option;

GameMain::GameMain(){
	stage1.initMap();
	option.init();
}


GameMain::~GameMain()
{
}

void GameMain::MainLoop() {
	//�Q�[���̃��C�����[�v
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		keyM.UpdateKeyState();	//�L�[�̍X�V
		time++;					//�S�̎��Ԃ̍X�V
		DrawFormatString(0, 0, GetColor(200, 200, 200), "%d", time);
		FpsFunction();

		stage1.scrollTest();
		stage1.drawMap();

		//���ׂĂ̕`��n�N���X��1�̐e�N���X����h������΃|�C���^�ŌĂׂ�悤�ɂȂ�͂�
		//option.Update();
		//option.Draw();
	}
}
