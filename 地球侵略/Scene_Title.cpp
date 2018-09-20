#include <string>
#include "Scene_Title.h"
#include "KeyManager.h"

typedef struct {
	char name[32];
	char explanation[64];	//�g��Ȃ���
	int x, y;
}RootmenuElement;

const int TITLE_NUM = 4;
const int DefaultPosX = 340;
int nowSelect = 0;

RootmenuElement TitleMenu[TITLE_NUM] = {	//���ۂ̒l�̐ݒ�
	{ "�`���[�g���A��","�͂��߂Ă̕��͂�����", DefaultPosX, 250 },
	{ "�N���J�n","�X�e�[�W�I�����Ă�", DefaultPosX, 300 },
	{ "���ʐݒ�" ,"�C�ɐH��Ȃ���Β��߂��Ă�", DefaultPosX, 350 },
	{ "���ɋA��" ,"�Q�[������߂������͂�����",DefaultPosX, 400 },
};

Scene_Title::Scene_Title() {
	SoundM.SetMusic(LoadSoundMem("data/mc/menu1.ogg"));
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
		if (nowSelect == 1 && false) {
			nowSelect = (nowSelect + 1) % TITLE_NUM;				//�I����Ԃ��������
		}
		SoundM.Se("data/mc/pick up.wav");
	}
	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || (keyM.GetKeyFrame(KEY_INPUT_UP) >= 15 && keyM.GetKeyFrame(KEY_INPUT_UP) % 4 == 0)) {		//��L�[��������Ă�����
		nowSelect = (nowSelect + (TITLE_NUM - 1)) % TITLE_NUM;	//�I����Ԃ���グ��
		if (nowSelect == 1 && false) {
			nowSelect = (nowSelect + (TITLE_NUM - 1)) % TITLE_NUM;	//�I����Ԃ���グ��

		}
		SoundM.Se("data/mc/pick up.wav");
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		switch (nowSelect) {
		case 0:
			SceneM.ChangeScene(scene::Game, 0);//��
			break;
		case 1:
			SceneM.ChangeScene(scene::Select);
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
		DrawString(TitleMenu[i].x, TitleMenu[i].y, TitleMenu[i].name, 0xFFFFFF);
	}
	DrawString(20, 560, TitleMenu[nowSelect].explanation, 0x000000);
	DrawString(550, 560, "���őI���EZ�Ō���", 0x000000);
	SetFontSize(-1);
}
