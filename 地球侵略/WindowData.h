#pragma once
#include "DxLib.h"
#include <string>
/**
ウィンドウそのものに関する情報を管理
ウィンドウサイズもインスタンスから取得
*/
class WindowData {
private:
	const std::string TITLE;
	bool is_fullscreen = false;
	bool ask_screenmode();

public:
	WindowData();
	~WindowData();

	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	
	int Init();

};

//WindowData.cpp内で定義済み
extern WindowData window;