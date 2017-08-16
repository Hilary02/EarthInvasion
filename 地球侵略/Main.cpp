#include "Main.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//ウィンドウ初期化
	if (window.Init() == -1) return -1;

	GameMain gamemain;
	gamemain.MainLoop();

	DxLib_End();
	return 0;
}