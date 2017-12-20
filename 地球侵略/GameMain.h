#pragma once
#include "DxLib.h"


/**
ゲームシーンの呼び出しの管理を行う．
会社でいえば部長職みたいな
*/


class GameMain{
public:
	GameMain();
	~GameMain();
	void MainLoop();//ゲーム全体の流れ

	enum SCENE { LOGO, TITLE, SELECT, PLAY, OPTION};
	SCENE scene;	//シーンごとに区別した列挙型

private:
	//現在は表示したいクラスをここで読みこんでしまっているが，ポインタを用いて必要分だけ読みこめるように
	int time = 0;

};

