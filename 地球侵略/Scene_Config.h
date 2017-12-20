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
	const static int MENU_NUM = 5;
	//�ǂꂪ�I������Ă���̂�
	enum OPTION_SELECT {
		BGM, SE, KEY, PAD, EXIT
	};
	enum OPTION_DRAW {
		VOL_CON, KEY_CON, PAD_CON
	};
	//���j���[�̕`��ꏊ�Ɠ��e���܂Ƃ߂�
	typedef struct {
		int x, y;			// ���W�i�[�p�ϐ�
		char name[32];		// ���ږ��i�[�p�ϐ�
	} MenuElement_t;

	MenuElement_t MenuElement[MENU_NUM] = {	//���ۂ̒l�̐ݒ�
		{ 400, 280, "BGM" },
		{ 400, 310, "SE" },
		{ 400, 340, "KEY" },
		{ 400, 370, "PAD" },
		{ 400, 400, "Back to Title" }
	};
	int nowSelect;
	int nowDraw;
	bool isKeyConfig = false;
public:
	// �L�[���͂ɉ����ăR���t�B�O������s���֐�
	void MoveCursor();
};

