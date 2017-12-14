#include "GameMain.h"
#include "KeyManager.h"
#include "FPS.h"
#include "SceneManager.h"
#include "WindowData.h"

//���݂͕\���������N���X�������œǂ݂���ł��܂��Ă��邪�C�|�C���^��p���ĕK�v�������ǂ݂��߂�悤��
int time = 0;


GameMain::GameMain(){
	SoundM.SetSound(LoadSoundMem("data/mc/���j���[���.wav"));
}


GameMain::~GameMain()
{
}

void GameMain::MainLoop() {
	//�Q�[���̃��C�����[�v
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		keyM.UpdateKeyState();	//�L�[�̍X�V
		time++;					//�S�̎��Ԃ̍X�V

		SoundM.SoundPlayer();

		SceneM.Update();
		SceneM.Draw();
		
		//�f�o�b�N�\��
		FpsFunction(window.WINDOW_WIDTH - 80,0);
		DrawFormatString(window.WINDOW_WIDTH-120, 20, GetColor(255, 125, 255), "Frame:%d", time);
	}
}
