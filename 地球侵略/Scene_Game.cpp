#include "Scene_Game.h"
#include "SceneManager.h"
#include "KeyManager.h"

typedef struct {
	char name[32];
	int x, y;
}RootmenuElement;
constexpr int MENU_NUM = 3;

RootmenuElement PauseMenu[MENU_NUM] = {	//���ۂ̒l�̐ݒ�
	{ "�ĊJ", 150, 250 },
	{ "�X�e�[�W�Z���N�g�ɖ߂�", 150, 300 },
	{ "�^�C�g���ɖ߂�" , 150, 350 },
};

Scene_Game::Scene_Game(int param) {
	nowStage = new Stage_Base(param);
	stageID = param;
	pauseBgL = LoadGraph("data/img/pausemenu.png");
	pauseBgR = LoadGraph("data/img/pausemenu.png");
	cursor = LoadGraph("data/img/cursor.png");
	SceneM.isPausing = false;

}

Scene_Game::~Scene_Game() {
	delete nowStage;
	InitGraph();
}

void Scene_Game::update() {
	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		isPause = !isPause;
		SceneM.isPausing = isPause;
		selecting = 0;
	}
	if (!isPause) {
		nowStage->update();
	}
	else {
		//�|�[�Y���j���[
		UpdatePause();
	}
}

void Scene_Game::Draw() {
	nowStage->draw();
	if (isPause) {
		DrawPause();

	}
}

void Scene_Game::UpdatePause() {
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {	//���L�[��������Ă�����
		selecting = (selecting + 1) % MENU_NUM;				//�I����Ԃ��������
		if (selecting == 1 && false) {
			selecting = (selecting + 1) % MENU_NUM;				//�I����Ԃ��������
		}
		SoundM.Se("data/mc/pick up.wav");
	}
	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || (keyM.GetKeyFrame(KEY_INPUT_UP) >= 15 && keyM.GetKeyFrame(KEY_INPUT_UP) % 4 == 0)) {		//��L�[��������Ă�����
		selecting = (selecting + (MENU_NUM - 1)) % MENU_NUM;	//�I����Ԃ���グ��
		if (selecting == 1 && false) {
			selecting = (selecting + (MENU_NUM - 1)) % MENU_NUM;	//�I����Ԃ���グ��

		}
		SoundM.Se("data/mc/pick up.wav");
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		if (selecting == 0) {
			isPause = false;
			SceneM.isPausing = false;
		};
		if (selecting == 1)	SceneM.ChangeScene(scene::Select, stageID);
		if (selecting == 2) SceneM.ChangeScene(scene::Title);
	}
}

void Scene_Game::DrawPause() {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	DrawGraph(0, 0, pauseBgL, true);
	DrawGraph(400, 0, pauseBgR, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawString(50, 50, "PAUSE MENU", 0xFFFFFF);
	DrawGraph(PauseMenu[selecting].x - 30, PauseMenu[selecting].y, cursor, TRUE);

	for (int i = 0; i < MENU_NUM; i++) { // ���j���[���ڂ�`��
		DrawString(PauseMenu[i].x, PauseMenu[i].y, PauseMenu[i].name, 0xFFFFFF);
	}

}
