#include "Scene_Title.h"

#include "KeyManager.h"


typedef struct {
	char name[16];
	char explanation[32];
	int x, y;
}RootmenuElement;

const int TITLE_NUM = 3;
const int DefaultPosX = 250;
int nowSelect = 0;

RootmenuElement TitleMenu[TITLE_NUM] = {	//実際の値の設定
	{ "Game","ゲーム画面へ", DefaultPosX, 50 },
	{ "Config" ,"コンフィグ画面へ", DefaultPosX, 80 },
	{ "Exit" ,"ゲーム終了",DefaultPosX, 110 },
};


Scene_Title::Scene_Title()
{
	SoundM.SetSound(LoadSoundMem("data/mc/メニュー画面.wav"));	
}


Scene_Title::~Scene_Title()
{
}

void Scene_Title::update(){
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {	//下キーが押されていたら
		nowSelect = (nowSelect + 1) % TITLE_NUM;				//選択状態を一つ下げる
		SoundM.Se(LoadSoundMem("data/mc/se_Z.mp3"));
	}
	if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || (keyM.GetKeyFrame(KEY_INPUT_UP) >= 15 && keyM.GetKeyFrame(KEY_INPUT_UP) % 4 == 0)) {		//上キーが押されていたら
		nowSelect = (nowSelect + (TITLE_NUM - 1)) % TITLE_NUM;	//選択状態を一つ上げる
		SoundM.Se(LoadSoundMem("data/mc/se_Z.mp3"));
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		switch (nowSelect) {
		case 0:
			SceneM.ChangeScene(scene::Game);
			break;
		case 1:
			SceneM.ChangeScene(scene::Config);
			break;
		case 2:
			DxLib_End();
			break;
		}
	}
}

void Scene_Title::Draw(){
	SoundM.SoundPlayer();
	DrawString(0, 0, "タイトル(デバッグ表示）", 0xFFFFFF);
	for (int i = 0; i < TITLE_NUM; i++) {
		if (i == nowSelect) {
			TitleMenu[i].x = DefaultPosX-20; // 座標をずらす
		}
		else {
			TitleMenu[i].x = DefaultPosX;
		}
	}
	for (int i = 0; i < TITLE_NUM; i++) { // メニュー項目を描画
		DrawString(TitleMenu[i].x, TitleMenu[i].y, TitleMenu[i].name, 0xFFFFFF);
	}
	DrawString(50, 520, TitleMenu[nowSelect].explanation, 0xFFFFFF);

}
