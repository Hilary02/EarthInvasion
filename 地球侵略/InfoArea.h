#pragma once
#include <DxLib.h>
#include "Player.h"

/*
ゲーム画面下部に表示される情報エリア関係．

*/
constexpr int baseX = 0;
constexpr int baseY = 520;

class InfoArea
{


public:

	//InfoArea();
	InfoArea(Player* pl);
	~InfoArea();
	void update();
	void draw();

private:
	//int baseX = 50;
	//int baseY = 100;
	int col_black = 0x000000;
	int hp = 0;
	Player *player;
	int hpbar;
	int hpbar_empty;
	int hpbar_width = 8;
	int hpbar_height = 16;
};

