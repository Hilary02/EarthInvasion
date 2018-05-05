#include "Stage_Base.h"
#include <assert.h>
#include <fstream>
#include <iostream>//ファイル入出力
#include <string>
#include <sstream> //文字ストリーム
#include "KeyManager.h"
#include "SoundManager.h"
#include "SceneManager.h"

Stage_Base::Stage_Base() {}

Stage_Base::Stage_Base(int stage) {
	stageId = stage;
	SoundM.SetSound(LoadSoundMem("data/mc/ビルの屋上、危険伴わず.wav"));

	//マップ地形の読み込み
	//ここを複数ステージ用に書き換え
	readStageData(0);

	objectMgr = new ObjectManager(vmap, stageId);
	//プレイヤー呼び出し
	this->player = objectMgr->getPlayer();
	player->setAbsolutePos(playerX, playerY);


	//制限時間 ttp://nanoappli.com/blog/archives/3229
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
	DrawGraphF(((800 - bgWidth) *((drawX) / (float)(MAP_WIDTH*CHIPSIZE))), -200, bgHand, false);	//背景の描画
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
	int limitDrawY = MAP_HEIGHT * CHIPSIZE - window.WINDOW_HEIGHT + 150;

	drawX = min(max(0, baseDrawX), limitDrawX);
	drawY = min(max(0, baseDrawY), limitDrawY);
}

//もっとスマートな方法ないかな？
int Stage_Base::readStageData(int stage) {
	std::string first = "data/stagedata/";
	std::string type = "summary";
	std::string id = std::to_string(0);	//ここをidに
	std::string csv = ".csv";

	std::string path = first + type + id + csv;
	readSummary(path);

	type = "map";
	path = first + type + id + csv;
	readMap(path);

	return 0;
}

int Stage_Base::readSummary(std::string file) {
	std::string str;	//行を格納
	std::string buf;	//値を格納
	std::vector<int> splited;

	std::ifstream ifs(file);	//ファイルのオープン
	if (!ifs) return -1;

	getline(ifs, str);	//先頭行の読み飛ばし
	getline(ifs, str);	//2行目だけ読む
	std::istringstream stream(str);
	while (getline(stream, buf, ',')) {
		splited.push_back(std::stoi(buf));
	}

	chipsetId = splited[0];
	bgmId = splited[1];
	playerX = splited[2];
	playerY = splited[3];
	time = splited[4] * 1000;	//msに変換
	return 0;
}

int Stage_Base::readMap(std::string file) {
	std::string str;	//行を格納
	std::string buf;	//値を格納
	int temp;
	std::ifstream ifs(file);	//ファイルのオープン
	if (!ifs) return -1;

	while (getline(ifs, str)) {
		std::vector<int> splited;
		std::istringstream stream(str);
		while (getline(stream, buf, ',')) {
			if (buf.size() != 0) {
				temp = std::stoi(buf);		//int型に変更
			}
			else {
				temp = 0;
			}
			splited.push_back(temp);
		}
		vmap.push_back(splited);
	}
	MAP_WIDTH = vmap[0].size();	//マップ幅の代表として一番最初を格納
	MAP_HEIGHT = vmap.size();

	ifs.close();
	return 1;
}

//仮も仮なので後で分離
int Stage_Base::loadImg() {
	//画像の設定
	chipImg[2] = LoadGraph("data/img/groundFloor.png");
	chipImg[3] = LoadGraph("data/img/airFloor.png");
	bgHand = LoadGraph("data/img/bg_factory.png");
	int t;
	GetGraphSize(bgHand, &bgWidth, &t);

	//InfoArea用
	img_hpbar = LoadGraph("data/img/hpbar.png");
	img_hpbar_empty = LoadGraph("data/img/hpbar_empty.png");


	return 1;
}

int Stage_Base::drawInfo() {
	//背景 そのうち画像になるか？
	DrawBox(infoX, infoY, 800, 600, 0x878773, TRUE);
	//HP表示欄 MAX15まで
	DrawFormatString(infoX + 40, infoY + 40, 0x000000, "HP:");
	for (int i = 0; i < 15; i++) {
		int x = infoX + 65 + i * (hpbar_width + 2);
		if (i < player->getHp()) {
			DrawGraph(x, infoY + 40, img_hpbar, false);
		}
		else {
			DrawGraph(x, infoY + 40, img_hpbar_empty, false);
		}
	}
	//制限時間表示欄
	DrawFormatString(infoX + 300, infoY + 50, 0xFFFFFF, "残り時間  %02d:%02d'%02d", leftTime / 60000/*分*/, (leftTime % 60000) / 1000/*秒*/, ((leftTime % 60000) % 1000) / 10 /*ms*/);
	return 0;
}
