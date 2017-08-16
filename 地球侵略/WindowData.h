#pragma once
#include "DxLib.h"
#include <string>

class WindowData {
private:
	const std::string TITLE;


public:
	WindowData();
	~WindowData();

	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	int Init();
};

//WindowData.cpp���Œ�`�ς�
extern WindowData window;