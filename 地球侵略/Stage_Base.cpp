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
	//マップ地形の読み込み
	//ここを複数ステージ用に書き換え
	if (readStageData(stage) == -1) {
		printfDx("Read Error");
	}
	SoundM.SetMusic(LoadSoundMem(bgmPath.c_str()));
	objectMgr = new ObjectManager(vmap, stageId, this);
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
	if (!(isDeadAnimation || isClearAnimation)) { //どちらもFalse ->アニメなしなら
		//タイマー
		leftTime = int(timeLimit - GetNowCount());
		if (leftTime <= 0) {
			SceneM.ChangeScene(scene::GameOver);
		}

		drawChipNum = 0;

		//死んでもクリアしてもなければオブジェクトを更新
		if (!isDeadAnimation && !isClearAnimation) {
			objectMgr->update();
		}
		scrollMap();	//プレイヤー座標に応じた表示範囲の変更
	}
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

	if (isClearAnimation) {
		DrawGraph(0, 0, img_clear, true);
		ChangeFontType(DX_FONTTYPE_EDGE);
		DrawString(250, 400, "Zキーでセレクト画面へ", 0xFFFFFF);
		ChangeFontType(DX_FONTTYPE_NORMAL);
		if (animationCounter <= 500) {
			animationCounter++;
		}
		if (keyM.GetKeyFrame(KEY_INPUT_Z) >= 1 || animationCounter >= 500) {
			isfadeOut = true;
		}
		if (isfadeOut) {
			fadeCounter += 5;
		}

		if (animationCounter <= 255 && animationCounter % 2 == 0) {
			player->setAbsolutePos(player->getX(), player->getY() - 1);
		}
		int br = 255 - fadeCounter;
		SetDrawBright(br, br, br);

		printfDx("%d\n", animationCounter);
		if (br <= 0) {
			//SetDrawBright(255, 255, 255);
			SoundM.SetMusic(LoadSoundMem("data/mc/menu1.ogg"));

			SceneM.ChangeScene(scene::Select, stageId);
		}
	}
	if (isDeadAnimation) {
		animationCounter++;
		player->setAbsolutePos(player->getX(), player->getY() + 3);
		int br = 255 - animationCounter * 2;
		SetDrawBright(br, br, br);

		printfDx("%d\n", br);
		if (br <= 0) {
			SetDrawBright(255, 255, 255);

			SceneM.ChangeScene(scene::GameOver, stageId);
		}
	}

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

void Stage_Base::PlayAnimation(int type) {
	if (!isDeadAnimation && !isClearAnimation) {
		if (type == 0) {
			SoundM.SetMusic(LoadSoundMem("data/mc/GameOver.ogg"),false);
			isDeadAnimation = true;
		}
		if (type == 1) {
			SoundM.SetMusic(LoadSoundMem("data/mc/Clear.ogg"), false);
			isClearAnimation = true;
		}
	}
}

//もっとスマートな方法ないかな？
int Stage_Base::readStageData(int stage) {
	std::string first = "data/stagedata/";
	std::string type = "summary";
	std::string id = std::to_string(stage);	//ここをidに
	std::string csv = ".csv";

	std::string path = first + type + id + csv;
	if (readSummary(path) == -1) return -1;

	type = "map";
	path = first + type + id + csv;
	if (readMap(path) == -1) return -1;

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
	for (int i = 0; i < 5; i++) {
		getline(stream, buf, ',');
		switch (i) {
		case 0: chipsetPath = buf; break;
		case 1: bgmPath = buf; break;
		case 2:	playerX = std::stoi(buf); break;
		case 3:	playerY = std::stoi(buf); break;
		case 4:	time = std::stoi(buf) * 1000; break;	//ms
		default: break;
		}
	}
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

	img_clear = LoadGraph("data/img/clear_img.png");

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
