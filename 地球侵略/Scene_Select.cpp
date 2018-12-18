#include "Scene_Select.h"

Scene_Select::Scene_Select(int param) {
	SoundM.SetMusic(LoadSoundMem("data/mc/menu1.ogg"));
	int clearedNum = 0;
	savedata.load();
	for (unsigned int i = 0; i <= stage_num; i++) {
		clearState[i] = savedata.getClearFlag(i);
	}
	//���[�h�����i�K�ł́C�N���A�ς݂�1�C�����łȂ����̂�0�ƂȂ��Ă���D����𒧐�\�Ȃ��̂ƕs�\�Ȃ��̂ɕ�����D

	clearState[0] = 1;	//����ł��Ȃ��X�e�[�W�D��{�I�ɃA�N�Z�X���Ȃ�
	for (unsigned int i = 1; i <= stage_num; i++) {
		int r1 = stageFrameData[i].requireStage1;
		int r2 = stageFrameData[i].requireStage2;
		if (clearState[i] == 0) {
			if (i >= 9 && i <= 10 && clearState[i - 1] == 1) {
				clearState[i] = 3;	//���N���A�̃{�X�X�e�[�W�̂�����ԏ������X�e�[�W��3�Ԃ�
			}
			if ((clearState[r1] & clearState[r2]) == 1) {	//�r�b�g���Z�D�v���X�e�[�W������1�Ȃ�����𖞂���
				clearState[i] = 2;
			}
		}
	}
	/* 0:����s��
	1:�N���A��
	2:���N���A(�����)
	3:��������\��(���߂̃{�X�X�e�[�W)
	*/
	bg = LoadGraph("data/img/stageselect.png");
	over = LoadGraph("data/img/stageselect_over.png");
	eeyan = LoadGraph("data/img/eeyan_map.png");

	if (1 <= param && param <= stage_num) {
		selecting = param;
	}
}


Scene_Select::~Scene_Select() {
	DeleteGraph(bg);
}

void Scene_Select::update() {
	//���قǑ����̈ړ�������킯�ł͂Ȃ��ƍl���C�����������͂�������폜����
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || keyM.GetKeyFrame(KEY_INPUT_LEFT) == 1 || keyM.GetKeyFrame(KEY_INPUT_RIGHT) == 1) {
		int nextSelect = 1;
		//if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {	//���L�[��������Ă�����
		if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1) { nextSelect = stageFrameData[selecting].D; }
		if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1) { nextSelect = stageFrameData[selecting].U; }
		if (keyM.GetKeyFrame(KEY_INPUT_LEFT) == 1) { nextSelect = stageFrameData[selecting].L; }
		if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) == 1) { nextSelect = stageFrameData[selecting].R; }
		if (clearState[nextSelect] == 1 || clearState[nextSelect] == 2) {	//�I���ł���X�e�[�W�������ꍇ 
			SoundM.Se("data/mc/pick up.wav");
			selecting = nextSelect;
		}
	}

	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		SceneM.ChangeScene(scene::Game, selecting);
	}
	if (keyM.GetKeyFrame(KEY_INPUT_X) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
}

void Scene_Select::Draw() {
	DrawGraph(0, 0, bg, TRUE);
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
	int col_yel = 0xFFFF00;

	for (int i = 1; i <= stage_num; i++) {
		int bx = stageFrameData[i].x;
		int by = stageFrameData[i].y;
		int color = col_blk;
		switch (clearState[i]) {
		case 0:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);	//���Ȃ�Z��
			color = col_blk;
			break;
		case 1:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 170);	//����
			color = col_yel;
			break;
		case 2:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);	//���\������
			color = col_blue;
			break;
		case 3:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 210);	//���������
			color = col_blk;
			break;
		default:
			color = 0xFF00FF;
			break;
		}

		DrawBox(bx, by, bx + 100, by + 100, color, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	int bx = stageFrameData[selecting].x;
	int by = stageFrameData[selecting].y;
	//	DrawThickBox(bx, by, bx + stageFrameData[selecting].w, by + stageFrameData[selecting].h, 0xFF0000, 3);
	//NOTE �������̕\��


	DrawGraph(0, 0, over, TRUE);
	DrawGraph(stageFrameData[selecting].x - 15, stageFrameData[selecting].y - 60, eeyan, TRUE);
	SetFontSize(20);
	DrawFormatString(25,570,0xFFFFFF,"Stage%2d", selecting);
	SetFontSize(-1);

}

void Scene_Select::DrawThickBox(int x1, int y1, int x2, int y2, unsigned int Color, int Thickness) {
	DrawLine(x1, y1, x1, y2, Color, Thickness);
	DrawLine(x1, y2, x2, y2, Color, Thickness);
	DrawLine(x2, y2, x2, y1, Color, Thickness);
	DrawLine(x2, y1, x1, y1, Color, Thickness);
}
