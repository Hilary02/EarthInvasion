#include "Scene_Game.h"
#include "SceneManager.h"
#include "KeyManager.h"

Scene_Game::Scene_Game() {
	//nowStage = new Stage_Base;
	int clearedNum = 0;
	savedata.load();
	for (unsigned int i = 0; i < clearState.size(); i++) {
		clearState[i] = savedata.getClearFlag(i);
	}
	//���[�h�����i�K�ł́C�N���A�ς݂�1�C�����łȂ����̂�0�ƂȂ��Ă���D����𒧐�\�Ȃ��̂ƕs�\�Ȃ��̂ɕ�����D

	clearState[0] = 1;	//����ł��Ȃ��X�e�[�W�D��{�I�ɃA�N�Z�X���Ȃ�
	for (unsigned int i = 1; i < clearState.size(); i++) {
		int r1 = stageFrameData[i].requireStage1;
		int r2 = stageFrameData[i].requireStage2;
		if (clearState[i] == 0 && (clearState[r1] & clearState[r2]) == 1) {	//�r�b�g���Z�D�v���X�e�[�W������1�Ȃ�����𖞂���
			clearState[i] = 2;
		}
	}
	bg_stageselect = LoadGraph("data/img/bg_stageselect.png");
}


Scene_Game::~Scene_Game() {
	if (!stageSelecting) {
		delete nowStage;
		DeleteGraph(bg_stageselect);
	}
}

void Scene_Game::update() {
	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
	if (stageSelecting) {
		selectUpdate();
	}
	else {
		nowStage->update();
	}
}

void Scene_Game::Draw() {
	if (stageSelecting) {
		selectDraw();
	}
	else {
		nowStage->draw();
	}
}

void Scene_Game::selectUpdate() {
	//���قǑ����̈ړ�������킯�ł͂Ȃ��ƍl���C�����������͂�������폜����
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) ==1|| keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || keyM.GetKeyFrame(KEY_INPUT_LEFT) == 1 || keyM.GetKeyFrame(KEY_INPUT_RIGHT) == 1) {
		int nextSelect = 1;
		//if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {	//���L�[��������Ă�����
		if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1) { nextSelect = stageFrameData[nowSelect].D; }
		if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1) { nextSelect = stageFrameData[nowSelect].U; }
		if (keyM.GetKeyFrame(KEY_INPUT_LEFT) == 1) { nextSelect = stageFrameData[nowSelect].L; }
		if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) == 1) { nextSelect = stageFrameData[nowSelect].R; }
		if (clearState[nextSelect] != 0) {	//�I���ł���X�e�[�W�������ꍇ 
			SoundM.Se(LoadSoundMem("data/mc/pick up.wav"));
			nowSelect = nextSelect;
		}

	}

	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		stageSelecting = false;
		nowStage = new Stage_Base(nowSelect);
	}
}



void Scene_Game::selectDraw() {
	DrawGraph(0, 0, bg_stageselect, TRUE);
	int textColor = 0x000000;
	for (unsigned int i = 0; i < clearState.size(); i++) {
		switch (clearState[i]) {
		case 0:
			textColor = 0x909090; //����s�\
			break;
		case 1:
			textColor = 0xFF0000; //�N���A��
			break;
		case 2:
			textColor = 0xFFFFFF; //����\
			break;
		default:
			textColor = 0x0000FF;	//�Ȃ񂩂̗�O
			break;
		}
		//DrawFormatString(150, i * 20, textColor, "Stage%d", i);
	}
	//DrawFormatString(120, nowSelect * 20, 0xFFFFFF, "��");

	//��
	int col_blk = 0x000000;
	int col_blue = 0x0000FF;
	int col_red = 0xFF0000;

	clsDx();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	for (int i = 1; i <= 13; i++) {
		printfDx("%d,", clearState[i]);
		int bx = stageFrameData[i].x;
		int by = stageFrameData[i].y;
		int color = col_blk;
		switch (clearState[i]) {
		case 0:
			color = col_blk;
			break;
		case 1:
			color = col_blue;
			break;
		case 2:
			color = col_red;
			break;
		default:
			color = 0xFF00FF;
			break;
		}

		DrawBox(bx, by, bx + stageFrameData[i].w, by + stageFrameData[i].h
			, color, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	int bx = stageFrameData[nowSelect].x;
	int by = stageFrameData[nowSelect].y;
	DrawBox(bx, by, bx + stageFrameData[nowSelect].w, by + stageFrameData[nowSelect].h
		, 0xFF0000, false);

}
