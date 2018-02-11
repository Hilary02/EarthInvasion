#include "Stage_Base.h"
#include <assert.h>
#include <fstream>
#include <iostream>//ファイル入出力
#include <string>
#include <sstream> //文字ストリーム
#include "KeyManager.h"
#include "SoundManager.h"
#include "SceneManager.h"

Stage_Base::Stage_Base(){}

Stage_Base::Stage_Base(int stage) {
	stageId = stage;
	//コードや外部ファイルに書くくらいならcsvから読み取ったほうが利便性高そう？
	//Arrayにするなら大きめに取っておくとか．Vectorだと広いステージになったときの読み込み速度が心配．
	MAP_HEIGHT = 30;
	MAP_WIDTH = 128;
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

	//ここを複数ステージ用に書き換え
	readMap("data/map/stage0.csv");

	//プレイヤー呼び出し

	objectMgr = new ObjectManager(vmap,stageId);
	this->player = objectMgr->getPlayer();


	//制限時間 ttp://nanoappli.com/blog/archives/3229
	time = 120'000;
	//DXライブラリの機能ではなくC++の機能で実装したい
	//現在，一時停止とか完全に無視して時間が進む
	timeLimit = GetNowCount() + time;

	//地形画像の読み込み
	//TODO:ステージごとの引数をつける
	loadImg();
}

Stage_Base::~Stage_Base() {
	vmap.clear();
	delete objectMgr;
	InitGraph();
}

void Stage_Base::update() {
	//タイマー
	leftTime = int(timeLimit - GetNowCount());
	if (leftTime <= 0) {
		SceneM.ChangeScene(scene::GameOver);
	}

	drawChipNum = 0;
	objectMgr->update();
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
	objectMgr->Draw(drawX, drawY);
	drawInfo();

	//デバッグ情報
//d	DrawFormatString(0, 30, GetColor(255, 125, 255), "マップ表示原点：%d  ,%d", drawX, drawY);
//d	DrawFormatString(0, 50, GetColor(255, 125, 255), "表示画像数：%d", drawChipNum);
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
	ifs.close();
	return 1;
}

//仮も仮なので後で分離
int Stage_Base::loadImg() {
	//画像の設定
	chipImg[2] = LoadGraph("data/img/groundFloor.png");
	chipImg[7] = LoadGraph("data/img/airFloor.png");
	bgHand = LoadGraph("data/img/bg01.jpg");

	//InfoArea用
	img_hpbar = LoadGraph("data/img/hpbar.png");
	img_hpbar_empty = LoadGraph("data/img/hpbar_empty.png");


	return 1;
}

int Stage_Base::drawInfo(){
	//背景 そのうち画像になるか？
	DrawBox(infoX, infoY, 800, 600, 0x878773, TRUE);
	//HP表示欄 MAX15まで
	DrawFormatString(infoX + 40, infoY + 40, 0x000000, "HP:");
	for (int i = 0; i < 15; i++) {
		int x = infoX + 65 + i*(hpbar_width + 2);
		if (i < player->getHp()) {
			DrawGraph(x, infoY + 40, img_hpbar, false);
		}
		else {
			DrawGraph(x, infoY + 40, img_hpbar_empty, false);
		}
	}
	//制限時間表示欄
	DrawFormatString(infoX+300, infoY+50, 0xFFFFFF, "残り時間  %02d:%02d'%02d", leftTime / 60000/*分*/, (leftTime % 60000) / 1000/*秒*/, ((leftTime % 60000) % 1000)/10 /*ms*/);
	return 0;
}
