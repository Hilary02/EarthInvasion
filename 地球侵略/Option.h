#pragma once
#define MENU_NUM 5
/**
�I�v�V������ʂ̏������s���D
�I�v�V�����̃Z�[�u�@�\���܂��Ȃ��̂ł��Ȃ��Ⴂ���Ȃ�
*/
class Option {
public:
	Option();
	~Option();
	void Update();
	void Draw();
private:
	// ���y�n���h��
	int bgm;
	int se;
	int *music;
	// ����
	int bgmVolume;
	int seVolume;
	int *volume;

	//�ǂꂪ�I������Ă���̂�
	enum OPTION_SELECT {
		BGM, SE, KEY, PAD, EXIT
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
public:
	// �L�[���͂ɉ����ăR���t�B�O������s���֐�
	void MoveCursor();
	void init();
};

extern Option option;