#include <string>
#include "Scene_Title.h"
#include "KeyManager.h"

typedef struct {
	char name[32];
	char explanation[64];	//使わない説
	int x, y;
}RootmenuElement;

const int TITLE_NUM = 4;
const int DefaultPosX = 380;
int nowSelect = 0;

RootmenuElement TitleMenu[TITLE_NUM] = {	//実際の値の設定
	{ "体験版","ステージのデモが遊べます", DefaultPosX, 250 },
	{ "ステージセレクト","まだステージはないのでUIだけ見ることができます", DefaultPosX, 300 },
	{ "設定" ,"音量の調節ができます", DefaultPosX, 350 },
	{ "Exit" ,"ゲーム終了",DefaultPosX, 400 },
};

Scene_Title::Scene_Title() {
	SoundM.SetSound(LoadSoundMem("data/mc/menu1.ogg"));
	bg = LoadGraph("data/img/bg_title.png");
	cursor = LoadGraph("data/img/cursor.png");
}

Scene_Title::~Scene_Title() {
	DeleteGraph(bg);
	DeleteGraph(cursor);
}

void Scene_Title::update() {
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {	//下キーが押されていたら
		nowSelect = (nowSelect + 1) % TITLE_NUM;				//選択状態を一つ下げる
		if (nowSelect == 1 && false) {
			nowSelect = (nowSelect + 1) % TITLE_NUM;				//選択状態を一つ下げる
		}
		SoundM.Se(LoadSoundMem("data/mc/pick up.wav"));
	}
	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || (keyM.GetKeyFrame(KEY_INPUT_UP) >= 15 && keyM.GetKeyFrame(KEY_INPUT_UP) % 4 == 0)) {		//上キーが押されていたら
		nowSelect = (nowSelect + (TITLE_NUM - 1)) % TITLE_NUM;	//選択状態を一つ上げる
		if (nowSelect == 1 && false) {
			nowSelect = (nowSelect + (TITLE_NUM - 1)) % TITLE_NUM;	//選択状態を一つ上げる

		}
		SoundM.Se(LoadSoundMem("data/mc/pick up.wav"));
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		switch (nowSelect) {
		case 0:
			SceneM.ChangeScene(scene::Game, 0);//仮
			break;
		case 1:
			SceneM.ChangeScene(scene::Select);
			break;
		case 2:
			SceneM.ChangeScene(scene::Config);
			break;
		case 3:
			DxLib_End();
			break;
		}
	}
}

void Scene_Title::Draw() {
	SetFontSize(24);
	SoundM.SoundPlayer();
	DrawGraph(0, 0, bg, TRUE);

	//for (int i = 0; i < TITLE_NUM; i++) {
	//	if (i == nowSelect) {
	//		TitleMenu[i].x = DefaultPosX - 20; // 座標をずらす
	//	}
	//	else {
	//		TitleMenu[i].x = DefaultPosX;
	//	}
	//}
	DrawGraph(DefaultPosX - 30, TitleMenu[nowSelect].y, cursor, TRUE);

	for (int i = 0; i < TITLE_NUM; i++) { // メニュー項目を描画
		if (i == 1) {
			DrawString(TitleMenu[i].x, TitleMenu[i].y, TitleMenu[i].name, 0x777777);

		}
		else {

			DrawString(TitleMenu[i].x, TitleMenu[i].y, TitleMenu[i].name, 0x000000);
		}
	}
	DrawString(20, 560, TitleMenu[nowSelect].explanation, 0x000000);
	SetFontSize(-1);
}
