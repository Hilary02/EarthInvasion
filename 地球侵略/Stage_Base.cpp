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
	//地形画像の読み込み
	//TODO:ステージごとの引数をつける
	loadImg();
	objectMgr = new ObjectManager(vmap, stageId, this);
	//プレイヤー呼び出し
	this->player = objectMgr->getPlayer();
	player->setAbsolutePos(playerX, playerY);
	befX = player->getX();
	befY = player->getY();


	//制限時間 ttp://nanoappli.com/blog/archives/3229
	leftTime = time;
	dTime = 0;
	beforeTime = GetNowCount();

}

Stage_Base::~Stage_Base() {
	vmap.clear();
	delete objectMgr;
	InitGraph();
}

void Stage_Base::update() {
	if (!(isDeadAnimation || isClearAnimation)) { //どちらもFalse ->アニメなしなら
		//タイマー
		if (!(SceneM.isPausing)) {
			leftTime -= int(dTime);
		}
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
	//タイマー
	dTime = (GetNowCount() - beforeTime);
	beforeTime = GetNowCount();


	DrawGraphF(((800 - bgWidth) *((drawX) / (float)(MAP_WIDTH*CHIPSIZE))), -200, bgHand, false);	//背景の描画
	int baseChipY = max(0, drawY - CHIPSIZE * 2);
	int baseChipX = max(0, drawX - CHIPSIZE * 2);

	//地形ブロックの描画
	for (int y = baseChipY / CHIPSIZE; y < ((drawY + window.WINDOW_HEIGHT - 50) / CHIPSIZE); y++) {
		for (int x = baseChipX / CHIPSIZE; x < ((drawX + CHIPSIZE + window.WINDOW_WIDTH) / CHIPSIZE); x++) {

			if (y < MAP_HEIGHT && x < MAP_WIDTH) {
				int tempX = (x * CHIPSIZE) - drawX;
				int tempY = (y * CHIPSIZE) - drawY;

				if (1 <= vmap[y][x] && vmap[y][x] <= 9 || 60 <= vmap[y][x] && vmap[y][x] <= 69) {
					DrawGraph(tempX, tempY, chipImg[vmap[y][x]], TRUE);
					drawChipNum++;
				}
			}
		}
	}
	objectMgr->Draw(drawX, drawY);

	//前面地形ブロックの描画
	for (int y = baseChipY / CHIPSIZE; y < ((drawY + window.WINDOW_HEIGHT - 50) / CHIPSIZE); y++) {
		for (int x = baseChipX / CHIPSIZE; x < ((drawX + CHIPSIZE + window.WINDOW_WIDTH) / CHIPSIZE); x++) {

			if (y < MAP_HEIGHT && x < MAP_WIDTH) {
				int tempX = (x * CHIPSIZE) - drawX;
				int tempY = (y * CHIPSIZE) - drawY;

				if (50 <= vmap[y][x] && vmap[y][x] <= 59) {
					DrawGraph(tempX, tempY, chipImg[vmap[y][x]], TRUE);
					drawChipNum++;
				}
			}
		}
	}

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

		//printfDx("%d\n", animationCounter);
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
		if (br <= 0) {
			SetDrawBright(255, 255, 255);

			SceneM.ChangeScene(scene::GameOver, stageId);
		}
	}

	//チュートリアルのやつ
	if (stageId == 0) {
		DrawRotaGraph(625, 88, 0.5, 0, img_tutorial, TRUE);
	}

	//デバッグ情報
//d	DrawFormatString(0, 30, GetColor(255, 125, 255), "マップ表示原点：%d  ,%d", drawX, drawY);
//d	DrawFormatString(0, 50, GetColor(255, 125, 255), "表示画像数：%d", drawChipNum);
}


void Stage_Base::scrollMap() {
	//プレイヤーの向きに応じて視界を変化
	bool dir = player->getDirection();
	int pX = player->getX();
	int pY = player->getY();
	if ((pX - befX) == 0) {
		if (dir) {
			visibleX -= AvisibleX;
			if (visibleX <= MinvisibleX)visibleX = MinvisibleX;
		}
		else {
			visibleX += AvisibleX;
			if (visibleX >= MaxvisibleX)visibleX = MaxvisibleX;
		}
	}
	befX = pX;
	befY = pY;

	int baseDrawX = player->getX() - visibleX;
	int baseDrawY = player->getY() - visibleY;
	int limitDrawX = MAP_WIDTH * CHIPSIZE - window.WINDOW_WIDTH;
	int limitDrawY = MAP_HEIGHT * CHIPSIZE - window.WINDOW_HEIGHT + 150;

	drawX = min(max(0, baseDrawX), limitDrawX);
	drawY = min(max(0, baseDrawY), limitDrawY);
}

void Stage_Base::PlayAnimation(int type) {
	if (!isDeadAnimation && !isClearAnimation) {
		if (type == 0) {
			SoundM.SetMusic(LoadSoundMem("data/mc/GameOver.ogg"), false);
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
	for (int i = 0; i < 6; i++) {
		getline(stream, buf, ',');
		switch (i) {
		case 0: chipsetPath = buf; break;
		case 1: bgPath = buf; break;
		case 2: bgmPath = buf; break;
		case 3:	playerX = std::stoi(buf); break;
		case 4:	playerY = std::stoi(buf); break;
		case 5:	time = std::stoi(buf) * 1000; break;	//ms
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
	MAP_WIDTH = (int)(vmap[0].size());	//マップ幅の代表として一番最初を格納
	MAP_HEIGHT = (int)(vmap.size());

	ifs.close();
	return 1;
}

//仮も仮なので後で分離
int Stage_Base::loadImg() {
	//画像の設定
	chipImg[2] = LoadGraph("data/img/groundFloor.png");
	chipImg[3] = LoadGraph("data/img/airFloor.png");
	chipImg[50] = LoadGraph("data/img/mapchipf0.png");
	chipImg[51] = LoadGraph("data/img/mapchipf1.png");
	chipImg[52] = LoadGraph("data/img/mapchipf2.png");
	chipImg[53] = LoadGraph("data/img/mapchipf3.png");
	chipImg[54] = LoadGraph("data/img/mapchipf4.png");
	chipImg[55] = LoadGraph("data/img/mapchipf5.png");
	chipImg[56] = LoadGraph("data/img/mapchipf6.png");
	chipImg[57] = LoadGraph("data/img/mapchipf7.png");
	chipImg[58] = LoadGraph("data/img/mapchipf8.png");
	chipImg[59] = LoadGraph("data/img/mapchipf9.png");
	chipImg[60] = LoadGraph("data/img/mapchip_60.png");
	chipImg[61] = LoadGraph("data/img/mapchip_61.png");
	chipImg[62] = LoadGraph("data/img/mapchip_62.png");
	chipImg[63] = LoadGraph("data/img/mapchip_63.png");
	chipImg[64] = LoadGraph("data/img/mapchip_64.png");
	chipImg[65] = LoadGraph("data/img/mapchip_65.png");
	chipImg[66] = LoadGraph("data/img/mapchip_66.png");
	chipImg[67] = LoadGraph("data/img/mapchip_67.png");
	chipImg[68] = LoadGraph("data/img/mapchip_68.png");
	chipImg[69] = LoadGraph("data/img/mapchip_69.png");

	bgHand = LoadGraph(bgPath.c_str());

	int t;
	GetGraphSize(bgHand, &bgWidth, &t);

	//InfoArea用
	img_hpbar = LoadGraph("data/img/hpbar.png");
	img_hpbar_empty = LoadGraph("data/img/hpbar_empty.png");
	img_tutorial = LoadGraph("data/img/tutorial.png");
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
