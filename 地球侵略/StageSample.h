#pragma once

#include <vector>
#include "DxLib.h"
#include "IOcsv.h"
/**
変更必要なところ多数．
マップチップサイズの変更やクラス分け

主人公の移動はStageクラスで管理をしてもいいのかもしれない
敵の情報格納配列，アイテムの配列．．．のように各オブジェクト毎に管理配列を作成し，
ポインタを用いてアクセスできればステージ毎に柔軟なステージ作成が行えると考える．

現在，キャラクタの座標もマップ全体の座標で管理ができている．

マップチップのデータが1-9で足りているため，20番以降を用いて敵情報の保存とかできるかもしれない．
別ファイルでも管理もできるが，マップ座標をいちいち調べながら打たなければいけなくなる．


*/
class StageSample
{
public:
	StageSample();
	~StageSample();
	
	int initMap();	//マップの初期化や読み込み
	void drawMap();	//マップの描画

	// 仮なのでいつかクラスに分離する
	void scrollTest();
	void scrollMap();	// プレイヤーの座標から表示するマップの起点を決定する関数．

private:
	const int MAP_HEIGHT;	//縦方向マップチップ数
	const int MAP_WIDTH;	//横方向マップチップ数
	const int CHIPSIZE = 32;//マップチップの大きさ
	
	int chipImg[10];		//マップチップ格納用配列

	std::vector<std::vector <int>> vmap;	//マップデータ格納

	//VectorMAP,ArrayMAPの意味でつけていた
	//こちらは必要がなくなる
	//決めうち
	int amap[60][234];
	int* p_map;

	//削除予定　描画原点を探してた
	int relativeX=0;
	int relativeY=0;

private:
	//削除予定
	int mapX;
	int mapY;


	//仮作成:プレイヤーの座標
	int playerX;
	int playerY;

	//描画する際の左上座標
	int drawX;
	int drawY;
	
};

