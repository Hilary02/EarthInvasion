#include "Stage_Base.h"
#include <assert.h>
#include <fstream>
#include <iostream>//ファイル入出力
#include <string>
#include <sstream> //文字ストリーム
#include <vector>
#include "SoundManager.h"

Stage_Base::Stage_Base() :
	//コンストラクタの引数に設定されないといけない
	MAP_HEIGHT(30)
	, MAP_WIDTH(128) {
	SoundM.SetSound(LoadSoundMem("data/mc/ビルの屋上、危険伴わず.wav"));
	//08.18　vectorのサイズを動的に変更できるようにした
	//指定したマップサイズで配列を確保
	//参考にしたところ
	//http://d.hatena.ne.jp/tei3344/20130207/1360238838

	//マップの領域の確保
	assert(MAP_HEIGHT >= 0);
	assert(MAP_WIDTH >= 0);
	vmap.resize(MAP_HEIGHT);
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			vmap[i].push_back(j);
		}
	}
	//マップ地形の読み込み
	readMap("data/map/tutrial-map改良版32.csv");
	//プレイヤー呼び出し
	player = new Player(vmap);
	player->setAbsolutePos(360, 600);
	//地形画像の読み込み
	//TODO:引数をつける
	loadImg();
}


Stage_Base::~Stage_Base() {
	delete player;
}

void Stage_Base::update() {
	totalFrame++;
	drawChipNum = 0;
	player->Update();
	scrollMap();	//プレイヤー座標に応じた表示範囲の変更
}

void Stage_Base::draw() {
	//DrawGraph(0, 0, bgHand, false);	//背景の描画
	int baseChipY = max(0, drawY - CHIPSIZE * 2);
	int baseChipX = max(0, drawX - CHIPSIZE * 2);
	for (int y = baseChipY / CHIPSIZE; y < ((drawY + window.WINDOW_HEIGHT - 50) / CHIPSIZE); y++) {
		for (int x = baseChipX / CHIPSIZE; x < ((drawX + CHIPSIZE + window.WINDOW_WIDTH) / CHIPSIZE); x++) {

			if (y < MAP_HEIGHT && x < MAP_WIDTH) {
				int tempX = (x * CHIPSIZE) - drawX;
				int tempY = (y * CHIPSIZE) - drawY;

				if (1 <= vmap[y][x] && vmap[y][x] <= 9) {
					DrawGraph(tempX, tempY, chipImg[vmap[y][x]], TRUE);
					drawChipNum++;
				}

				//if (vmap[y][x] == 9) {
				//	DrawGraph(tempX, tempY + 16, chipImg[vmap[y][x]], TRUE);
				//	drawChipNum++;
				//}
			}
		}
	}
	
	player->Draw(drawX, drawY);
	//デバッグ情報
	DrawFormatString(0, 30, GetColor(255, 125, 255), "マップ表示原点：%d  ,%d", drawX, drawY);
	DrawFormatString(0, 50, GetColor(255, 125, 255), "表示画像数：%d", drawChipNum);
}


void Stage_Base::scrollMap() {
	//TODO:数字はいずれconst変数にする
	int baseDrawX = player->getX() - 100;
	int baseDrawY = player->getY() - 300;
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
			if (buf.size() != 0) {
				temp = std::stoi(buf);		//int型に変更
			}
			else {
				temp = 0;
			}

			this->vmap[y][x] = temp;			//vectorもアクセス方法は配列と同様に行える
		}
	}
	return 1;
}

//仮も仮なので後で分離
int Stage_Base::loadImg() {
	//画像の設定
	LoadDivGraph("data/img/20170823174821.png", 10, 10, 1, 32, 32, chipImg);
	//chipImg[1] = LoadGraph("data/img/airFloor.png");
	chipImg[2] = LoadGraph("data/img/groundFloor.png");
	//chipImg[3] = LoadGraph("data/img/eeyanWait.png");
	chipImg[4] = LoadGraph("data/img/enemy1Wait.png");
	chipImg[5] = LoadGraph("data/img/healPot.png");
	chipImg[6] = LoadGraph("data/img/lockDoor.png");
	chipImg[7] = LoadGraph("data/img/airFloor.png");
	chipImg[8] = LoadGraph("data/img/moveGround.png");
	chipImg[9] = LoadGraph("data/img/togetoge.png");
	bgHand = LoadGraph("data/img/bg01.jpg");
	return 1;

}