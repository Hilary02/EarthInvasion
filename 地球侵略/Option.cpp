#include "DxLib.h"
#include "Option.h"
#include "KeyManager.h"


Option::Option() {
}


Option::~Option()
{
}

void Option::init() {
	//���ŉ����𗘗p���Ă��܂��D
	//BGM�̓Z�����A���CSE��http://dova-s.jp/se/play278.html����q�؁D
	bgm = LoadSoundMem("data/mc/cell.mp3");
	se = LoadSoundMem("data/mc/se_Z.mp3");
	bgmVolume = 255;
	seVolume = 200;
	nowSelect = BGM;
	nowDraw = VOL_CON;
}

void Option::Update() {
	MoveCursor();
}



void Option::Draw() {
	DrawFormatString(0, 20, GetColor(255, 255, 255), "�ݒ�e�X�g %d", nowSelect);
	//DrawString(0, 20, "Esc�L�[�������ƃ��j���[��ʂɖ߂�܂��B", GetColor(255, 255, 255));

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
	DrawFormatString(430, 280, GetColor(255, 255, 255), ": %d", bgmVolume);
	DrawFormatString(430, 310, GetColor(255, 255, 255), ": %d", seVolume);

	

}


// �L�[���͂ɉ����ăR���t�B�O������s���֐�
void Option::MoveCursor() {

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
		volume = &bgmVolume;
		music = &bgm;
	}
	if (nowSelect == SE) {
		volume = &seVolume;
		music = &se;
	}

	if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
		if (nowSelect == BGM || nowSelect == SE) {
			*volume = ((*volume)++ < 255) ? (*volume)++ : 255;//���ʂ��グ��.Max255
			ChangeVolumeSoundMem(*volume, *music);				//��������̉��ʕύX
			if (nowSelect == SE) PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);
		}
	}	else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
		if (nowSelect == BGM || nowSelect == SE) {
			*volume = ((*volume)-- > 0) ? (*volume)-- : 0;//���ʂ�������.Min0
			ChangeVolumeSoundMem(*volume, *music);
			if (nowSelect == SE) PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);
		}
	}

	//���y�̍Đ��E��~�̃T���v���D���ʂ��ω����Ă��邩�m���߂邽�߂ɂ���
	if (keyM.GetKeyFrame(KEY_INPUT_SPACE) == 1) {
		if (CheckSoundMem(bgm) == 0) {
			PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);
		}
		else {
			StopSoundMem(bgm);
		}
	}
	if (CheckSoundMem(bgm) == 0) {
		DrawFormatString(0, 60, GetColor(255, 255, 255), "STOP");
	}

	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		switch (nowSelect) {
		case KEY:
			isKeyConfig = true;
			break;
		case PAD:
			break;
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

