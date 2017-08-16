#include "WindowData.h"

//windowを用いて初期化など行う．
WindowData window;

WindowData::WindowData() :
	WINDOW_WIDTH(800),
	WINDOW_HEIGHT(600),
	TITLE("LEI_v0.1") {
}


WindowData::~WindowData()
{
}

int WindowData::Init() {
	ChangeWindowMode(true);
	SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32);
	if (DxLib_Init() == -1)	return -1;
	SetMainWindowText(TITLE.c_str());				//c_strでchar型にできる
	SetBackgroundColor(0, 0, 0);					//背景色を黒に
	//SetOutApplicationLogValidFlag(false);			//ログ出力
	//SetTransColor(255, 0, 255);					//透過色未設定
	SetAlwaysRunFlag(false);						//アクティブでないとき停止
	SetUseDXArchiveFlag(true);						//DXアーカイブ機能を使う

	SetDrawScreen(DX_SCREEN_BACK);					//裏画面に描画

	return 0;
}