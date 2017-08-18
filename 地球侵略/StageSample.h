#pragma once

#include <vector>
#include "DxLib.h"
#include "IOcsv.h"

class StageSample
{
public:
	StageSample();
	~StageSample();
	
	int initMap();	//マップの初期化や読み込み
	void drawMap();	//マップの描画

private:
	const int MAP_HEIGHT;	//縦方向マップチップ数
	const int MAP_WIDTH;	//横方向マップチップ数
	const int CHIPSIZE = 16;//マップチップの大きさ
	std::vector<std::vector <int>> vmap;
	//std::vector<int> map;
	//決めうち
	int amap[60][234];
	int* p_map;

	//削除予定
	int relativeX=0;
	int relativeY=0;

public:
	// 仮なのでいつかクラスに分離する
	void scrollTest();

private:
	int mapX;
	int mapY;

	//マップチップ格納用配列
	int chipImg[10];

	//仮作成:プレイヤーの座標
	int playerX;
	int playerY;

	//マップを描画する際の左上座標
	int drawX;
	int drawY;

public:
	// プレイヤーの座標から表示するマップの起点を決定する関数．
	void scrollMap();
};

