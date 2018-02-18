#include "Scene_Config.h"

Scene_Config::Scene_Config() {
	nowSelect = BGM;
	nowDraw = VOL_CON;
}

Scene_Config::~Scene_Config() {
	printfDx("Delete_Config\n");
}

void Scene_Config::update() {
	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
	MoveCursor();
}

void Scene_Config::Draw() {
	SetFontSize(30);
	DrawFormatString(20, 20, GetColor(255, 255, 255), "コンフィグ");

	for (int i = 0; i < MENU_NUM; i++) {
		if (i == nowSelect) {
			MenuElement[i].x = 380; // 座標を左にする
		}
		else {
			MenuElement[i].x = 400;
		}
	}
	for (int i = 0; i < MENU_NUM; i++) { // メニュー項目を描画
		DrawFormatString(MenuElement[i].x, MenuElement[i].y, 0xFFFFFF, MenuElement[i].name);
	}

	//音量を表示　関数に切り分けるかも
	DrawFormatString(430, 280, GetColor(255, 255, 255), ": %d", SoundM.Volume(0));
	DrawFormatString(430, 340, GetColor(255, 255, 255), ": %d", SoundM.Volume(1));

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
		SoundM.SoundVolume(0);
	}
	if (nowSelect == SE) {
		SoundM.SoundVolume(1);
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		switch (nowSelect) {
			//case KEY:
			//	isKeyConfig = true;
			//	break;
			//case PAD:
			//	break;
		case EXIT:
			SceneM.ChangeScene(scene::Title);
		default:
			break;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		switch (nowSelect) {
			//case KEY:
			//case PAD:
			//	isKeyConfig = false;
			//	break;
		default:
			break;
		}
	}
}

