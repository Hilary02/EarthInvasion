#pragma once

#include <vector>
#include "DxLib.h"
#include "IOcsv.h"

class StageSample
{
public:
	StageSample();
	~StageSample();
	int initMap();
	void drawStage();
private:
	const int MAP_HEIGHT;
	const int MAP_WIDTH;
	//std::vector<std::vector <int>> map;
	std::vector<int> map;
	//決めうち
	int amap[60][234];
	int* p_map;

	int relativeX=0;
	int relativeY=0;
public:
	// 仮なのでいつかクラスに分離する
	void scrollTest();
	char key[256];
private:
	int mapX;
	int mapY;

	//マップチップ格納用配列
	int chipImg[10];

	//仮作成:プレイヤーの座標
	int playerX;
	int playerY;
public:
	// プレイヤーの座標から表示するマップの起点を決定する関数．
	void scrollMap();
};

