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
	for (unsigned int i = 1; i < clearState.size(); i++) {
		if (i < 12 && i % 3 != 0) {
			if (clearState[i] == 1) clearedNum++;
			else clearState[i] = 2;//����\�ł��邱�Ƃ������D
		}
		if (i % 3 == 0) {
			if (clearState[i] == 1) clearedNum++;
			else if (clearState[i - 2] == 1 && clearState[i - 1] == 1)
				clearState[i] = 2; //����\�ł��邱�Ƃ������D
		}
		if (i == 13) {
			printfDx("\n%d\n", clearedNum);
			if (clearedNum > 12)clearState[i] = 2;  //����\�ł��邱�Ƃ������D
		}
	}
}


Scene_Game::~Scene_Game() {
	printfDx("Delete_Game");
	if (!stageSelecting) {
		delete nowStage;
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
	//�ʓ|�������̂ŕ��������D�����i�D�ǂ��Ȃ�񂶂�Ȃ��H
	/*�X�e�[�W0- �`���[�g���A��
	3�X�e�[�W���Ƃɒʏ�C�ʏ�C�{�X�̍\�� �{�X��2�̒ʏ�X�e���U�����Ă���
	13 ���X�{�X�H(12�܂ł��ׂăN���A�Œ���ł���)
	*/
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {	//���L�[��������Ă�����
		nowSelect = (nowSelect + 1) % 14;				//�I����Ԃ��������
		while (!(clearState[nowSelect] >= 1)) {
			nowSelect = (nowSelect + 1) % 14;				//�ǂ������ɂȂ�܂őI����Ԃ��������
		}
		printfDx("%d", nowSelect);
		SoundM.Se(LoadSoundMem("data/mc/pick up.wav"));
	}

	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || (keyM.GetKeyFrame(KEY_INPUT_UP) >= 15 && keyM.GetKeyFrame(KEY_INPUT_UP) % 4 == 0)) {		//��L�[��������Ă�����
		nowSelect = (nowSelect + (14 - 1)) % 14;	//�I����Ԃ���グ��
		while (!(clearState[nowSelect] >= 1)) {
			nowSelect = (nowSelect + (14 - 1)) % 14;
		}
		printfDx("%d", nowSelect);
		SoundM.Se(LoadSoundMem("data/mc/pick up.wav"));
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		stageSelecting = false;
		nowStage = new Stage_Base(0);

	}
}

void Scene_Game::selectDraw() {
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
		DrawFormatString(150, i * 20, textColor, "Stage%d", i);
	}
	DrawFormatString(120, nowSelect * 20, 0xFFFFFF, "��");
}
