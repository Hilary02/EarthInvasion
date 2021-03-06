#include "Scene_Config.h"

Scene_Config::Scene_Config() {
	nowSelect = BGM;
	nowDraw = VOL_CON;
	bg = LoadGraph("data/img/bg_config.png");
	cursor = LoadGraph("data/img/cursor.png");
	volBar = LoadGraph("data/img/volBar.png");
}

Scene_Config::~Scene_Config() {
	InitGraph();
}

void Scene_Config::update() {
	MoveCursor();
}

void Scene_Config::Draw() {
	DrawGraph(0, 0, bg, TRUE);
	SetFontSize(30);
	DrawFormatString(80, 50, GetColor(255, 255, 255), "コンフィグ");

	for (int i = 0; i < MENU_NUM; i++) { // メニュー項目を描画
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, 0xFFFFFF, MenuElement[i].name);
	}

	//カーソルを表示
	DrawGraph(MenuElement[nowSelect].x - 34, MenuElement[nowSelect].y + 4, cursor, false);

	//音量ゲージを表示
	for (int i = 0; i < SoundM.Volume(0); i++) {
		DrawGraph(530 + 25 * i, 270, volBar, false);
	}
	for (int i = 0; i < SoundM.Volume(1); i++) {
		DrawGraph(530 + 25 * i, 330, volBar, false);
	}

	SetFontSize(16);
}

// キー入力に応じてコンフィグ操作を行う関数
void Scene_Config::MoveCursor() {
	//長押ししていると連続スクロールをすることができる処理
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {
		nowSelect = (nowSelect + 1) % MENU_NUM;				//選択状態を一つ下げる
	}
	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || (keyM.GetKeyFrame(KEY_INPUT_UP) >= 15 && keyM.GetKeyFrame(KEY_INPUT_UP) % 4 == 0)) {
		nowSelect = (nowSelect + (MENU_NUM - 1)) % MENU_NUM;//選択状態を一つ上げる
	}
	//ボリューム調節機能．同じ処理になるのでポインタを利用して圧縮を図った．
	//配列でも問題ない気がしたが別段問題はないと思う．
	if (nowSelect == BGM) {
		SoundM.SoundVolume(Stype::BGM);
	}
	if (nowSelect == SE) {
		SoundM.SoundVolume(Stype::SE);
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		switch (nowSelect) {
		case EXIT:
			SceneM.ChangeScene(scene::Title);
			break;
		default:
			break;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
	if (keyM.GetKeyFrame(KEY_INPUT_X) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
}

