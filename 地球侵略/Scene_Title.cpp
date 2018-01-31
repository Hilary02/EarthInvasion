#include "Scene_Title.h"

#include "KeyManager.h"

#include <string>;


typedef struct {
	char name[16];
	char explanation[32];
	int x, y;
}RootmenuElement;

const int TITLE_NUM = 3;
const int DefaultPosX = 300;
int nowSelect = 0;

RootmenuElement TitleMenu[TITLE_NUM] = {	//���ۂ̒l�̐ݒ�
	{ "Game","�Q�[����ʂ�", DefaultPosX, 150 },
	{ "Config" ,"�R���t�B�O��ʂ�", DefaultPosX, 210 },
	{ "Exit" ,"�Q�[���I��",DefaultPosX, 270 },
};


Scene_Title::Scene_Title()
{
	SoundM.SetSound(LoadSoundMem("data/mc/���j���[���.wav"));	
	bg= LoadGraph("data/img/enemy1Wait.png");
}


Scene_Title::~Scene_Title()
{
}

void Scene_Title::update(){
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {	//���L�[��������Ă�����
		nowSelect = (nowSelect + 1) % TITLE_NUM;				//�I����Ԃ��������
		SoundM.Se(LoadSoundMem("data/mc/pick up.wav"));
	}
	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || (keyM.GetKeyFrame(KEY_INPUT_UP) >= 15 && keyM.GetKeyFrame(KEY_INPUT_UP) % 4 == 0)) {		//��L�[��������Ă�����
		nowSelect = (nowSelect + (TITLE_NUM - 1)) % TITLE_NUM;	//�I����Ԃ���グ��
		SoundM.Se(LoadSoundMem("data/mc/pick up.wav"));
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		switch (nowSelect) {
		case 0:
			//SceneM.ChangeScene(scene::Game);
			SceneM.ChangeScene(scene::StageSelect);

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
	SetFontSize(30);
	SoundM.SoundPlayer();

	//void DrawCenterString(int y, int screenX, int color, char *c) {
	//	DrawString(ScreenX / 2 - GetDrawStringWidth(c, strlen(c)) / 2, y, c, color);
	//}

	//DrawString(0, 0, "�^�C�g��(�f�o�b�O�\���j", 0xFFFFFF);

	std::string title = "�n���N�������������I �̌���";
	DrawString(400 - GetDrawStringWidth("�n���N�������������I �̌���",title.length()) / 2, 50, title.c_str(), 0xFFFFFF);



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
	SetFontSize(16);
}
