#include "Scene_Config.h"



Scene_Config::Scene_Config() {
	//仮で音源を利用しています．
	//BGMはセルリアン，SEはhttp://dova-s.jp/se/play278.htmlから拝借．
	bgm = LoadSoundMem("data/mc/cell.mp3");
	se = LoadSoundMem("data/mc/se_Z.mp3");
	bgmVolume = 255;
	seVolume = 200;
	nowSelect = BGM;
	nowDraw = VOL_CON;
}


Scene_Config::~Scene_Config() {
	DeleteSoundMem(bgm);
	DeleteSoundMem(se);
}

void Scene_Config::Update() {
	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
	MoveCursor();
}

void Scene_Config::Draw()
{
	DrawFormatString(0, 20, GetColor(255, 255, 255), "設定テスト %d", nowSelect);
	DrawString(0, 40, "Spaceキーを押すとBGM再生", GetColor(255, 255, 255));

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
	DrawFormatString(430, 280, GetColor(255, 255, 255), ": %d", bgmVolume);
	DrawFormatString(430, 310, GetColor(255, 255, 255), ": %d", seVolume);



}


// キー入力に応じてコンフィグ操作を行う関数
void Scene_Config::MoveCursor() {

	//長押ししていると連続スクロールをすることができる処理
	//いらない気もするけれど，困る事はないはずなのでつけとく
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {
		nowSelect = (nowSelect + 1) % MENU_NUM;				//選択状態を一つ下げる
	}
	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || (keyM.GetKeyFrame(KEY_INPUT_UP) >= 15 && keyM.GetKeyFrame(KEY_INPUT_UP) % 4 == 0)) {
		nowSelect = (nowSelect + (MENU_NUM - 1)) % MENU_NUM;//選択状態を一つ上げる
	}
	//ボリューム調節機能．同じ処理になるのでポインタを利用して圧縮を図った．
	//配列でも問題ない気がしたが別段問題はないと思う．
	if (nowSelect == BGM) {
		volume = &bgmVolume;
		sound = &bgm;
	}
	if (nowSelect == SE) {
		volume = &seVolume;
		sound = &se;
	}

	if (nowSelect == BGM || nowSelect == SE) {
		bool isVolChanged = false;
		if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
			*volume = ((*volume)++ < 255) ? (*volume)++ : 255;//音量を上げる.Max255
			isVolChanged = true;
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
			*volume = ((*volume)-- > 0) ? (*volume)-- : 0;//音量を下げる.Min0
			isVolChanged = true;
		}
		if (isVolChanged) {
			ChangeVolumeSoundMem(*volume, *sound);				//メモリ上の音量変更
			if (nowSelect == SE) PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);
			isVolChanged = false;
		}
	}

	//音楽の再生・停止のサンプル．音量が変化しているか確かめるためにつけた
	if (keyM.GetKeyFrame(KEY_INPUT_SPACE) == 1) {
		if (CheckSoundMem(bgm) == 0) {
			PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);
		}
		else {
			StopSoundMem(bgm);
		}
	}
	if (CheckSoundMem(bgm) == 0) {
		DrawFormatString(0, 60, GetColor(255, 255, 255), "STOP");
	}

	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		switch (nowSelect) {
		case KEY:
			isKeyConfig = true;
			break;
		case PAD:
			break;
		case EXIT:
			SceneM.ChangeScene(scene::Title);
		default:
			break;
		}
	}
	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		switch (nowSelect) {
		case KEY:
		case PAD:
			isKeyConfig = false;
			break;
		default:
			break;
		}
	}
}

