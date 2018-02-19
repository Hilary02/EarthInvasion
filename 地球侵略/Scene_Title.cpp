#include <string>
#include "Scene_Title.h"
#include "KeyManager.h"

typedef struct {
	char name[16];
	char explanation[32];	//�g��Ȃ���
	int x, y;
}RootmenuElement;

const int TITLE_NUM = 4;
const int DefaultPosX = 380;
int nowSelect = 1;

RootmenuElement TitleMenu[TITLE_NUM] = {	//���ۂ̒l�̐ݒ�
	{ "�`���[�g���A��","���K��", DefaultPosX, 250 },
	{ "�Q�[���X�^�[�g","�����C�N���ł�", DefaultPosX, 300 },
	{ "�ݒ�" ,"���ʂ̒���", DefaultPosX, 350 },
	{ "Exit" ,"�Q�[���I��",DefaultPosX, 400 },
};

Scene_Title::Scene_Title() {
	SoundM.SetSound(LoadSoundMem("data/mc/���j���[���.wav"));
	bg = LoadGraph("data/img/bg_title.png");
	cursor = LoadGraph("data/img/cursor.png");
}

Scene_Title::~Scene_Title() {
	DeleteGraph(bg);
	DeleteGraph(cursor);
}

void Scene_Title::update() {
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
			SceneM.ChangeScene(scene::Game);//��
			break;
		case 1:
			SceneM.ChangeScene(scene::Game);
			break;
		case 2:
			SceneM.ChangeScene(scene::Config);
			break;
		case 3:
			DxLib_End();
			break;
		}
	}
}

void Scene_Title::Draw() {
	SetFontSize(24);
	SoundM.SoundPlayer();
	DrawGraph(0, 0, bg, TRUE);

	//for (int i = 0; i < TITLE_NUM; i++) {
	//	if (i == nowSelect) {
	//		TitleMenu[i].x = DefaultPosX - 20; // ���W�����炷
	//	}
	//	else {
	//		TitleMenu[i].x = DefaultPosX;
	//	}
	//}
	DrawGraph(DefaultPosX - 30, TitleMenu[nowSelect].y, cursor, TRUE);

	for (int i = 0; i < TITLE_NUM; i++) { // ���j���[���ڂ�`��
		DrawString(TitleMenu[i].x, TitleMenu[i].y, TitleMenu[i].name, 0x000000);
	}
	SetFontSize(-1);
}
