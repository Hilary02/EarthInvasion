#include "Scene_Title.h"

#include "KeyManager.h"

typedef struct {
	char name[16];
	char explanation[32];
	int x, y;
}RootmenuElement;

const int TITLE_NUM = 3;
const int DefaultPosX = 250;
int nowSelect = 0;

RootmenuElement TitleMenu[TITLE_NUM] = {	//���ۂ̒l�̐ݒ�
	{ "Game","�Q�[����ʂ�", DefaultPosX, 50 },
	{ "Config" ,"�R���t�B�O��ʂ�", DefaultPosX, 80 },
	{ "Exit" ,"�Q�[���I��",DefaultPosX, 110 },
};


Scene_Title::Scene_Title()
{
}


Scene_Title::~Scene_Title()
{
}

void Scene_Title::Update(){
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {	//���L�[��������Ă�����
		nowSelect = (nowSelect + 1) % TITLE_NUM;				//�I����Ԃ��������
	}
	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || (keyM.GetKeyFrame(KEY_INPUT_UP) >= 15 && keyM.GetKeyFrame(KEY_INPUT_UP) % 4 == 0)) {		//��L�[��������Ă�����
		nowSelect = (nowSelect + (TITLE_NUM - 1)) % TITLE_NUM;	//�I����Ԃ���グ��
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		switch (nowSelect) {
		case 0:
			SceneM.ChangeScene(scene::Game);
			break;
		case 1:
			SceneM.ChangeScene(scene::Config);
			break;
		case 2:
			DxLib_End();
			break;
		}
	}
}

void Scene_Title::Draw(){
	DrawString(0, 0, "�^�C�g��(�f�o�b�O�\���j", 0xFFFFFF);
	for (int i = 0; i < TITLE_NUM; i++) {
		if (i == nowSelect) {
			TitleMenu[i].x = DefaultPosX-20; // ���W�����炷
		}
		else {
			TitleMenu[i].x = DefaultPosX;
		}
	}
	for (int i = 0; i < TITLE_NUM; i++) { // ���j���[���ڂ�`��
		DrawString(TitleMenu[i].x, TitleMenu[i].y, TitleMenu[i].name, 0xFFFFFF);
	}
	DrawString(50, 520, TitleMenu[nowSelect].explanation, 0xFFFFFF);

}
