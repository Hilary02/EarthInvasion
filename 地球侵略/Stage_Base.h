#pragma once
#include <vector>
#include <array>
#include "DxLib.h"
#include "WindowData.h"
#include "Player.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "SaveData.h"
/**
Stageクラスはまず地形を読み込む．
Playerクラス，ObjectManagerクラスに主人公の移動とそれ以外の処理を投げるので
このクラスはマップ座標と描画座標の変換をおもに担当する

マップチップのデータが1-9で足りているため，20番以降を用いて敵情報の保存とかできるかもしれない．
別ファイルでも管理もできるが，マップ座標をいちいち調べながら打たなければいけなくなる．
*/
class Stage_Base {
public:
	Stage_Base();
	Stage_Base(int stage);
	~Stage_Base();

	void update();	//更新処理
	void draw();	//描画処理
	void scrollMap();	// プレイヤーの座標から表示するマップの起点を決定する関数．

private:
	int readMap(std::string file);
	int loadImg();
	int drawInfo();

	//複数ステージに対応するためにconst外し中
	int MAP_HEIGHT;	//縦方向マップチップ数
	int MAP_WIDTH;	//横方向マップチップ数
	const int CHIPSIZE = 32;//マップチップの大きさ

	int chipImg[10];		//マップチップ格納用配列
	int bgHand;				//背景画像格納配列

	int lockdoor[3];        //ドア用格納配列
	int moveground[2];      //動く床用配列

	std::vector<std::vector <int>> vmap;	//マップデータ格納

	Player *player;
	ObjectManager *objectMgr;
	CollisionManager *colMgr;
	SaveData &savedata = SaveData::get_instance();

	//地形などを描画する際の左上座標
	int drawX, drawY;

	//情報表示エリアの原点
	int infoX = 0;
	int infoY = 520;
	int img_hpbar;
	int img_hpbar_empty;
	int hpbar_width = 8;
	int hpbar_height = 16;
	int stageId; //セーブ用

	//制限時間（）

	LONGLONG time;
	LONGLONG timeLimit;
	int leftTime;

	//デバッグ用データ
	int drawChipNum = 0;
};