#include "WindowData.h"

//window��p���ď������ȂǍs���D
WindowData window;

WindowData::WindowData() :
	WINDOW_WIDTH(800),
	WINDOW_HEIGHT(600),
	TITLE("�n���N�����������I �̌���") {
}


WindowData::~WindowData()
{
}

//�E�B���h�E�̏������������s���D
int WindowData::Init() {
	ChangeWindowMode(true);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	if (DxLib_Init() == -1)	return -1;
	SetMainWindowText(TITLE.c_str());				//c_str��char�^�ɂł���
	SetBackgroundColor(0, 0, 0);					//�w�i�F������
	//SetOutApplicationLogValidFlag(false);			//���O�o��
	//SetTransColor(255, 0, 255);					//���ߐF���ݒ�
	SetAlwaysRunFlag(false);						//�A�N�e�B�u�łȂ��Ƃ���~
	SetUseDXArchiveFlag(true);						//DX�A�[�J�C�u�@�\���g��

	SetDrawScreen(DX_SCREEN_BACK);					//����ʂɕ`��

	return 0;
}