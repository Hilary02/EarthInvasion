#include "GameMain.h"
#include "KeyManager.h"
#include "Option.h"


#include "FPS.h"

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
	while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0) {

		keyM.UpdateKeyState();	//キーの更新
		time++;
		DrawFormatString(0, 0, GetColor(200, 200, 200), "%d", time);
		//stage1.scrollTest();
		//stage1.drawMap();

		option.Update();
		option.Draw();
		FpsFunction();
	}
}
