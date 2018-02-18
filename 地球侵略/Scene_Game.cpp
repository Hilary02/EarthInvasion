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
			if (clearState[i] == 1) { clearedNum++; }
			else { clearState[i] = 2; }//挑戦可能であることを示す．
		}
		if (i % 3 == 0) {
			if (clearState[i] == 1) { clearedNum++; }
			else if (clearState[i - 2] == 1 && clearState[i - 1] == 1) { clearState[i] = 2; } //挑戦可能であることを示す．
		}
		if (i == 13) {
			if (clearedNum >= 12 && clearState[i] != 1)clearState[i] = 2;  //挑戦可能であることを示す．
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
	//面倒くさいので文字だけ．いつか格好良くなるんじゃない？
	/*ステージ0- チュートリアル
	3ステージごとに通常，通常，ボスの構成 ボスは2つの通常ステを攻略してから
	13 ラスボス？(12まですべてクリアで挑戦できる)
	*/
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {	//下キーが押されていたら
		nowSelect = (nowSelect + 1) % 14;				//選択状態を一つ下げる
		while (!(clearState[nowSelect] >= 1)) {
			nowSelect = (nowSelect + 1) % 14;				//良い感じになるまで選択状態を一つ下げる
		}
		printfDx("%d", nowSelect);
		SoundM.Se(LoadSoundMem("data/mc/pick up.wav"));
	}

	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || (keyM.GetKeyFrame(KEY_INPUT_UP) >= 15 && keyM.GetKeyFrame(KEY_INPUT_UP) % 4 == 0)) {		//上キーが押されていたら
		nowSelect = (nowSelect + (14 - 1)) % 14;	//選択状態を一つ上げる
		while (!(clearState[nowSelect] >= 1)) {
			nowSelect = (nowSelect + (14 - 1)) % 14;
		}
		printfDx("%d", nowSelect);
		SoundM.Se(LoadSoundMem("data/mc/pick up.wav"));
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		stageSelecting = false;
		nowStage = new Stage_Base(nowSelect);

	}
}

void Scene_Game::selectDraw() {
	int textColor = 0x000000;
	for (unsigned int i = 0; i < clearState.size(); i++) {
		switch (clearState[i]) {
		case 0:
			textColor = 0x909090; //挑戦不可能
			break;
		case 1:
			textColor = 0xFF0000; //クリア済
			break;
		case 2:
			textColor = 0xFFFFFF; //挑戦可能
			break;
		default:
			textColor = 0x0000FF;	//なんかの例外
			break;
		}
		DrawFormatString(150, i * 20, textColor, "Stage%d", i);
	}
	DrawFormatString(120, nowSelect * 20, 0xFFFFFF, "◇");
}
