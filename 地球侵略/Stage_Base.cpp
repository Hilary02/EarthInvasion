#include "Stage_Base.h"
#include <assert.h>
#include<fstream>
#include<iostream>//ファイル入出力
#include<string>
#include<sstream> //文字ストリーム
#include<vector>


Stage_Base::Stage_Base() :
	//コンストラクタの引数に設定されないといけない
	MAP_HEIGHT(30)
	, MAP_WIDTH(128) {
	//08.18　vectorのサイズを動的に変更できるようにした
	//指定したマップサイズで配列を確保
	//参考にしたところ
	//http://d.hatena.ne.jp/tei3344/20130207/1360238838

	//マップの要素の確保
	assert(MAP_HEIGHT >= 0);
	vmap.resize(MAP_HEIGHT);
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			vmap[i].push_back(j);
		}
	}
	readMap("data/map/tutrial-map改良版32.csv");	//マップ地形の読み込み
	loadImg();
	player.setAbsolutePos(400, 700);
}


Stage_Base::~Stage_Base() {
}

void Stage_Base::update(){

}

void Stage_Base::draw(){
	DrawGraph(0, 0, bgHand, false);	//背景の描画
}


void Stage_Base::scrollMap(){
	//最適化してくれるはず
	int baseDrawX = playerX - 100;
	int baseDrawY = playerY - 300;
	int limitDrawX = MAP_WIDTH * CHIPSIZE - window.WINDOW_WIDTH;
	int limitDrawY = MAP_HEIGHT* CHIPSIZE - window.WINDOW_HEIGHT + 150;

	drawX = min(max(0, baseDrawX), limitDrawX);
	drawY = min(max(0, baseDrawY), limitDrawY);
}

int Stage_Base::readMap(std::string file) {
	std::string str;	//行を格納
	std::string buf;	//値を格納
	int temp;
	//ファイルのオープン
	std::ifstream ifs(file);
	if (!ifs) return 1;

	for (int y = 0; y < this->MAP_HEIGHT; y++) {
		getline(ifs, str);				//csvファイルを1行読み込む
		std::istringstream stream(str);
		for (int x = 0; x < this->MAP_WIDTH; x++) {
			getline(stream, buf, ',');	//カンマで区切る

			try {
				temp = std::stoi(buf);		//int型に変更
			}
			catch (std::invalid_argument e) {
				temp = 0;
			}
			catch (std::out_of_range e) {
				temp = 0;
			}

			this->vmap[y][x] = temp;			//vectorもアクセス方法は配列と同様に行える
		}
	}
	return 1;
}

//仮も仮なので後で分離
int Stage_Base::loadImg(){
	//画像の設定
	LoadDivGraph("data/img/20170823174821.png", 10, 10, 1, 32, 32, chipImg);
	//chipImg[1] = LoadGraph("data/img/airFloor.png");
	chipImg[2] = LoadGraph("data/img/groundFloor.png");
	chipImg[3] = LoadGraph("data/img/eeyanWait.png");
	chipImg[4] = LoadGraph("data/img/enemy1Wait.png");
	chipImg[5] = LoadGraph("data/img/healPot.png");
	chipImg[6] = LoadGraph("data/img/lockDoor.png");
	chipImg[7] = LoadGraph("data/img/airFloor.png");
	chipImg[8] = LoadGraph("data/img/moveGround.png");
	chipImg[9] = LoadGraph("data/img/togetoge.png");
	bgHand = LoadGraph("data/img/bg01.jpg");
	return 1;
}

int Stage_Base::debugInfo(){
	int drawPics = 0;

	return 0;
}
