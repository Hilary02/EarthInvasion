#include "Scene_Config.h"

Scene_Config::Scene_Config() {
	nowSelect = BGM;
	nowDraw = VOL_CON;
	bg = LoadGraph("data/img/bg_config.png");
	cursor = LoadGraph("data/img/cursor.png");
	volBar = LoadGraph("data/img/volBar.png");
}

Scene_Config::~Scene_Config() {
}

void Scene_Config::update() {
	MoveCursor();
}

void Scene_Config::Draw() {
	DrawGraph(0, 0, bg, TRUE);
	SetFontSize(30);
	DrawFormatString(80, 50, GetColor(255, 255, 255), "�R���t�B�O");

	for (int i = 0; i < MENU_NUM; i++) { // ���j���[���ڂ�`��
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, 0xFFFFFF, MenuElement[i].name);
	}

	//�J�[�\����\��
	DrawGraph(MenuElement[nowSelect].x - 34, MenuElement[nowSelect].y + 4, cursor, false);

	//���ʃQ�[�W��\��
	for (int i = 0; i < SoundM.Volume(0); i++) {
		DrawGraph(530 + 25 * i, 270, volBar, false);
	}
	for (int i = 0; i < SoundM.Volume(1); i++) {
		DrawGraph(530 + 25 * i, 330, volBar, false);
	}

	SetFontSize(16);
}

// �L�[���͂ɉ����ăR���t�B�O������s���֐�
void Scene_Config::MoveCursor() {
	//���������Ă���ƘA���X�N���[�������邱�Ƃ��ł��鏈��
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {
		nowSelect = (nowSelect + 1) % MENU_NUM;				//�I����Ԃ��������
	}
	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || (keyM.GetKeyFrame(KEY_INPUT_UP) >= 15 && keyM.GetKeyFrame(KEY_INPUT_UP) % 4 == 0)) {
		nowSelect = (nowSelect + (MENU_NUM - 1)) % MENU_NUM;//�I����Ԃ���グ��
	}
	//�{�����[�����ߋ@�\�D���������ɂȂ�̂Ń|�C���^�𗘗p���Ĉ��k��}�����D
	//�z��ł����Ȃ��C���������ʒi���͂Ȃ��Ǝv���D
	if (nowSelect == BGM) {
		SoundM.SoundVolume(Stype::BGM);
	}
	if (nowSelect == SE) {
		SoundM.SoundVolume(Stype::SE);
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		switch (nowSelect) {
		case EXIT:
			SceneM.ChangeScene(scene::Title);
			break;
		default:
			break;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
	if (keyM.GetKeyFrame(KEY_INPUT_X) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
}

