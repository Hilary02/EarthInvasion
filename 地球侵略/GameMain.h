#pragma once
#include "DxLib.h"

#include "StageSample.h"



class GameMain{
public:
	GameMain();
	~GameMain();
	void MainLoop();//ゲーム全体の流れ

	enum SCENE { LOGO, TITLE, CHOICE, PLAY, OPTION};
	SCENE scene;	//シーンごとに区別した列挙型

private:

};

