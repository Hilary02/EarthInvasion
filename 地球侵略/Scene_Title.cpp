#include <string>
#include "Scene_Title.h"
#include "KeyManager.h"

typedef struct {
	char name[16];
	char explanation[32];	//使わない説
	int x, y;
}RootmenuElement;

const int TITLE_NUM = 4;
const int DefaultPosX = 380;
int nowSelect = 1;

RootmenuElement TitleMenu[TITLE_NUM] = {	//実際の値の設定
	{ "チュートリアル","練習台", DefaultPosX, 250 },
	{ "ゲームスタート","さあ，侵略です", DefaultPosX, 300 },
	{ "設定" ,"音量の調節", DefaultPosX, 350 },
	{ "Exit" ,"ゲーム終了",DefaultPosX, 400 },
};

Scene_Title::Scene_Title() {
	SoundM.SetSound(LoadSoundMem("data/mc/メニュー画面.wav"));
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
		SoundM.Se(LoadSoundMem("data/mc/pick up.wav"));
	}
	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || (keyM.GetKeyFrame(KEY_INPUT_UP) >= 15 && keyM.GetKeyFrame(KEY_INPUT_UP) % 4 == 0)) {		//上キーが押されていたら
		nowSelect = (nowSelect + (TITLE_NUM - 1)) % TITLE_NUM;	//選択状態を一つ上げる
		SoundM.Se(LoadSoundMem("data/mc/pick up.wav"));
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		switch (nowSelect) {
		case 0:
			SceneM.ChangeScene(scene::Game);//仮
			break;
		case 1:
			SceneM.ChangeScene(scene::Game);
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
		DrawString(TitleMenu[i].x, TitleMenu[i].y, TitleMenu[i].name, 0x000000);
	}
	SetFontSize(-1);
}
