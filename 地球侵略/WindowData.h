#pragma once
#include "DxLib.h"
#include <string>
/**
�E�B���h�E���̂��̂Ɋւ�������Ǘ�
�E�B���h�E�T�C�Y���C���X�^���X����擾
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

//WindowData.cpp���Œ�`�ς�
extern WindowData window;