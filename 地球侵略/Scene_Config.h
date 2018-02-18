#pragma once
#include "Scene_Frame.h"
#include "SoundManager.h"

class Scene_Config :
	public Scene_Frame
{
public:
	Scene_Config();
	~Scene_Config();
	void update();
	void Draw();
private:
	const static int MENU_NUM = 3;
	enum OPTION_SELECT {
		BGM, SE,  EXIT //�I�v�V�������j���[
	};
	enum OPTION_DRAW {
		VOL_CON, KEY_CON   //PAD�̐ݒ�͕ۗ�
	};
	//���j���[�̕`��ꏊ�Ɠ��e���܂Ƃ߂�
	typedef struct {
		int x, y;			// ���W�i�[�p�ϐ�
		char name[32];		// ���ږ��i�[�p�ϐ�
	} MenuElement_t;

	MenuElement_t MenuElement[MENU_NUM] = {	//���ۂ̈ʒu��l�̐ݒ�
		{ 400, 280, "BGM" },
		{ 400, 340, "SE" },	
		//{ 400, 340, "KEY" },
		//{ 400, 370, "PAD" },
		{ 400, 400, "Back to Title" }
	};
	int nowSelect;
	int nowDraw;
	bool isKeyConfig = false;
public:
	// �L�[���͂ɉ����ăR���t�B�O������s���֐�
	void MoveCursor();
};

