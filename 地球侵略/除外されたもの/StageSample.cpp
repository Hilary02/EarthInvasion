#include "StageSample.h"
#include "WindowData.h"
#include "KeyManager.h"

//#include "Player.h"


#include <assert.h>

int bgHand;

StageSample::StageSample() :
	//マップサイズとプレイヤーの初期位置を指定
	MAP_HEIGHT(30)
	, MAP_WIDTH(128)
	, playerX(400)
	, playerY(700)
{
	//08.18　vectorのサイズを動的に変更できるようにした
	//指定したマップサイズで配列を確保
	//参考にしたところ
	//http://d.hatena.ne.jp/tei3344/20130207/1360238838

	assert(MAP_HEIGHT >= 0);
	vmap.resize(MAP_HEIGHT);
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			vmap[i].push_back(j);
		}
	}
	initMap();
	player = new Player(vmap);
	player->setAbsolutePos(playerX, playerY);

	objectMgr = new ObjectManager(vmap);
}

StageSample::~StageSample()
{
}

int StageSample::initMap() {
	IOcsv::CSVtoVector("data/map/tutrial-map改良版32.csv", vmap, MAP_WIDTH, MAP_HEIGHT);

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

	LoadDivGraph("data/img/eeyanWait.png", 4, 4, 1, 64, 64, eeyanImg);
	debugCounter = 0;

	return 0;
}


void StageSample::drawMap() {
	debugCounter++;
	//背景
	DrawGraph(0, 0, bgHand, false);
	//デバッグ用画像のカウンタ
	int drawPics = 0;

	scrollMap();	//プレイヤー座標に応じた表示範囲の変更

	// -50はキャラ情報などを表示するための空間を確保するための値．50という値自体に意味はない．
	int ty = max(0, drawY - CHIPSIZE * 2);
	int tx = max(0, drawX - CHIPSIZE * 2);
	for (int y = ty / CHIPSIZE; y < ((drawY + window.WINDOW_HEIGHT - 50) / CHIPSIZE); y++) {
		for (int x = tx / CHIPSIZE; x < ((drawX + CHIPSIZE + window.WINDOW_WIDTH) / CHIPSIZE); x++) {
			if (y < MAP_HEIGHT && x < MAP_WIDTH) {

				int tempX = (x * CHIPSIZE) - drawX;
				int tempY = (y * CHIPSIZE) - drawY;

				//マップチップ代わりの中抜き四角
				//DrawBox(tempX, tempY, tempX + CHIPSIZE, tempY + CHIPSIZE, setColor, false);

				if (1 <= vmap[y][x] && vmap[y][x] <= 8) {
					DrawGraph(tempX, tempY, chipImg[vmap[y][x]], TRUE);
					drawPics++;
				}

				if (vmap[y][x] == 9) {
					DrawGraph(tempX, tempY + 16, chipImg[vmap[y][x]], TRUE);
					drawPics++;
				}
				//DrawFormatString(tempX + 2, tempY + 2, 0x000000, "%d", vmap[y][x]);

				//空白表示
				//else DrawBox(tempX, tempY, tempX + CHIPSIZE, tempY + CHIPSIZE, GetColor(0, 255, 0), FALSE);
			}
			//主人公の代わりの赤四角
			//マップ座標と描画原点から描画をしているため，カメラのみのスクロールも可能
			//DrawBox(playerX - drawX, playerY - drawY, playerX + CHIPSIZE * 2 - drawX, playerY + CHIPSIZE * 2 - drawY, GetColor(255, 0, 0), true);
		}
	}
	//デバッグ情報
	DrawFormatString(0, 30, GetColor(255, 125, 255), "マップ表示原点：%d  ,%d", drawX, drawY);
	DrawFormatString(0, 50, GetColor(255, 125, 255), "表示画像数：%d", drawPics);
	player->Update();
	player->Draw(drawX, drawY);

	objectMgr->Update();

	int img_id = (debugCounter / 15) % 4;
//	DrawGraph(playerX - drawX, playerY - drawY, eeyanImg[img_id], true);


	DrawBox( 0, window.WINDOW_HEIGHT - 80,  window.WINDOW_WIDTH, window.WINDOW_HEIGHT, 0x00FF00, true);
}


// 仮なのでいつかクラスに分離する
void StageSample::scrollTest() {
	int move = 5;
	if (keyM.GetKeyFrame(KEY_INPUT_UP) >= 1 && playerY - move >= 0) {
		playerY -= move;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 1 && playerY + move <= MAP_HEIGHT * CHIPSIZE) {
		playerY += move;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1 && playerX - move >= 0) {
		playerX -= move;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1 && playerX + move <= MAP_WIDTH * CHIPSIZE) {
		playerX += move;
	}

}

// プレイヤーの座標から表示するマップの起点を決定する関数．8.11 Hilary
//プレイヤーの表示位置もなんらかの変数に入れておきたい
void StageSample::scrollMap() {
	//最適化してくれるはず
	int baseDrawX = player->getX() - 500;
	int baseDrawY = player->getY() - 100;
	int limitDrawX = MAP_WIDTH * CHIPSIZE - window.WINDOW_WIDTH;
	int limitDrawY = MAP_HEIGHT* CHIPSIZE - window.WINDOW_HEIGHT + 150;

	drawX = min(max(0, baseDrawX), limitDrawX);
	drawY = min(max(0, baseDrawY), limitDrawY);
}
