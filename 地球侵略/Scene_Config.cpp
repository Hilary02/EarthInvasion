#include "Scene_Config.h"




Scene_Config::Scene_Config() {
	//���ŉ����𗘗p���Ă��܂��D
	//BGM�̓Z�����A���CSE��http://dova-s.jp/se/play278.html����q�؁D

	nowSelect = BGM;
	nowDraw = VOL_CON;
}


Scene_Config::~Scene_Config() {
}

void Scene_Config::update() {
	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
	MoveCursor();
}

void Scene_Config::Draw()
{
	DrawFormatString(0, 20, GetColor(255, 255, 255), "�ݒ�e�X�g %d", nowSelect);
	DrawString(0, 40, "Space�L�[��������BGM�Đ�", GetColor(255, 255, 255));

	for (int i = 0; i < MENU_NUM; i++) {
		if (i == nowSelect) {
			MenuElement[i].x = 380; // ���W�����ɂ���
		}
		else {
			MenuElement[i].x = 400;
		}
	}
	for (int i = 0; i < MENU_NUM; i++) { // ���j���[���ڂ�`��
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, 0xFFFFFF, MenuElement[i].name);
	}

	//���ʂ�\���@�֐��ɐ؂蕪���邩��
	DrawFormatString(430, 280, GetColor(255, 255, 255), ": %d", SoundM.Volume(0));
	DrawFormatString(430, 310, GetColor(255, 255, 255), ": %d", SoundM.Volume(1));



}


// �L�[���͂ɉ����ăR���t�B�O������s���֐�
void Scene_Config::MoveCursor() {

	//���������Ă���ƘA���X�N���[�������邱�Ƃ��ł��鏈��
	//����Ȃ��C�����邯��ǁC���鎖�͂Ȃ��͂��Ȃ̂ł��Ƃ�
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {
		nowSelect = (nowSelect + 1) % MENU_NUM;				//�I����Ԃ��������
	}
	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || (keyM.GetKeyFrame(KEY_INPUT_UP) >= 15 && keyM.GetKeyFrame(KEY_INPUT_UP) % 4 == 0)) {
		nowSelect = (nowSelect + (MENU_NUM - 1)) % MENU_NUM;//�I����Ԃ���グ��
	}
	//�{�����[�����ߋ@�\�D���������ɂȂ�̂Ń|�C���^�𗘗p���Ĉ��k��}�����D
	//�z��ł����Ȃ��C���������ʒi���͂Ȃ��Ǝv���D
	if (nowSelect == BGM) {
		SoundM.SoundVolume(0);
	}
	if (nowSelect == SE) {
		SoundM.SoundVolume(1);
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		switch (nowSelect) {
		case KEY:
			isKeyConfig = true;
			break;
		case PAD:
			break;
		case EXIT:
			SceneM.ChangeScene(scene::Title);
		default:
			break;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		switch (nowSelect) {
		case KEY:
		case PAD:
			isKeyConfig = false;
			break;
		default:
			break;
		}
	}
}

