#include "DxLib.h"
#include "WindowData.h"

int fpsTime[2] = { 0, }, count = 0;
double fps = 0.0;

//fpsを表示するだけ
void FpsFunction() {
	if (count == 0)
		fpsTime[0] = GetNowCount();						    //1周目の時間取得
	if (count == 59) {
		fpsTime[1] = GetNowCount();							//60周目の時間取得
		fps = 1000.0f / ((fpsTime[1] - fpsTime[0]) / 60.0f);//測定した値からfpsを計算
		count = 0;										//カウントを初期化
	}
	else count++;	//現在何周目かカウント
	if (fps != 0) DrawFormatString(window.WINDOW_WIDTH - 80, 0, GetColor(255, 125, 255), "fps %.1f", fps); //fpsを表示
	return;
}


//hanoi