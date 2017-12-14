#include "GameMain.h"
#include "KeyManager.h"
#include "FPS.h"
#include "SceneManager.h"
#include "WindowData.h"

//現在は表示したいクラスをここで読みこんでしまっているが，ポインタを用いて必要分だけ読みこめるように
int time = 0;


GameMain::GameMain(){
	SoundM.SetSound(LoadSoundMem("data/mc/メニュー画面.wav"));
}


GameMain::~GameMain()
{
}

void GameMain::MainLoop() {
	//ゲームのメインループ
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		keyM.UpdateKeyState();	//キーの更新
		time++;					//全体時間の更新

		SoundM.SoundPlayer();

		SceneM.Update();
		SceneM.Draw();
		
		//デバック表示
		FpsFunction(window.WINDOW_WIDTH - 80,0);
		DrawFormatString(window.WINDOW_WIDTH-120, 20, GetColor(255, 125, 255), "Frame:%d", time);
	}
}
