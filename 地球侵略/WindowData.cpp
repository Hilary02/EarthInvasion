#include "WindowData.h"
#include "resource.h"

//window��p���ď������ȂǍs���D
WindowData window;

bool WindowData::ask_screenmode() {
	if (MessageBox(NULL, "�t���X�N���[���ŋN�����܂����H", "�N���I�v�V����", MB_YESNO) == IDYES) {
		return true;
	}
	else {
		return false;
	}
}
WindowData::WindowData() :
	WINDOW_WIDTH(800),
	WINDOW_HEIGHT(600),
	TITLE("�n���N�����������I ver1.1") {
}


WindowData::~WindowData()
{
}

//�E�B���h�E�̏������������s���D
int WindowData::Init() {
	SetWindowIconID(IDI_ICON1);
	SetMainWindowText(TITLE.c_str());				//c_str��char�^�ɂł���
	//is_fullscreen = ask_screenmode();  //�R�����g�A�E�g�ŋ����E�B���h�E
	if (is_fullscreen) {
		ChangeWindowMode(FALSE);          //�t���X�N���[��
	}
	else {
		ChangeWindowMode(TRUE);           //�E�B���h�E���[�h�ŕ\��
		SetWindowSizeChangeEnableFlag(TRUE, TRUE);  // �E�C���h�E�T�C�Y��
		SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
		SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	}
	if (DxLib_Init() == -1)	return -1;
	SetBackgroundColor(0, 0, 0);					//�w�i�F������
	SetOutApplicationLogValidFlag(false);			//���O�o��
	//SetTransColor(255, 0, 255);					//���ߐF���ݒ�
	SetAlwaysRunFlag(false);						//�A�N�e�B�u�łȂ��Ƃ���~
	SetUseDXArchiveFlag(true);						//DX�A�[�J�C�u�@�\���g��

	SetDrawScreen(DX_SCREEN_BACK);					//����ʂɕ`��

	return 0;
}