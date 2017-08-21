#include "GameMain.h"
#include "KeyManager.h"
#include "FPS.h"

#include "StageSample.h"
#include "Option.h"

//現在は表示したいクラスをここで読みこんでしまっているが，ポインタを用いて必要分だけ読みこめるように
int time = 0;
StageSample stage1;
Option option;

GameMain::GameMain(){
	stage1.initMap();
	option.init();
}


GameMain::~GameMain()
{
}

void GameMain::MainLoop() {
	//ゲームのメインループ
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		keyM.UpdateKeyState();	//キーの更新
		time++;					//全体時間の更新
		DrawFormatString(0, 0, GetColor(200, 200, 200), "%d", time);
		FpsFunction();

		stage1.scrollTest();
		stage1.drawMap();

		//すべての描画系クラスを1つの親クラスから派生すればポインタで呼べるようになるはず
		//option.Update();
		//option.Draw();
	}
}
