#include "StageSample.h"
#include "WindowData.h"
#include "KeyManager.h"


StageSample::StageSample() :
	MAP_HEIGHT(60)
	, MAP_WIDTH(234)
	, playerX(100)
	, playerY(800)
{
	//map.resize(MAP_HEIGHT);
	//マップ配列要素用のメモリ確保
	//for (int i = 0; i < MAP_HEIGHT; i++) {
	//	map[i].resize(MAP_WIDTH);
	//}
	//どう定義するか迷走
	//std::vector< std::vector<int> > map(MAP_HEIGHT, std::vector<int>(MAP_WIDTH));
	//map = std::vector<std::vector<int>>(MAP_HEIGHT, std::vector<int>(MAP_WIDTH, 1));
	vmap.resize(MAP_HEIGHT);		// ()内の数字が要素数
	for (int i = 0; i<MAP_HEIGHT; i++) {
		vmap[i].resize(MAP_WIDTH);
	}
	//map.reserve(MAP_WIDTH*MAP_HEIGHT);

}


StageSample::~StageSample()
{
}



//DrawString(0, 0, "入力エラー", GetColor(255, 255, 255));


int StageSample::initMap() {
	p_map = &amap[0][0];
	IOcsv::Readcsv("data/map/チュートリアルマップ.csv", &amap[0][0], MAP_WIDTH, MAP_HEIGHT);
	//IOcsv::Readcsv("map02.csv", &vmap[0][0], MAP_WIDTH, MAP_HEIGHT);

	LoadDivGraph("data/img/mapchip10.png", 10, 10, 1, 16, 16, chipImg);
	return 0;

}


void StageSample::drawMap() {
	int setColor = GetColor(125, 125, 125);

	scrollMap();	//プレイヤー座標に応じた表示範囲の変更
	

	for (int i = 0; i < 10; i++) {
		DrawGraph(100 + i * 16, 100, chipImg[i], true);
	}

	// -50はキャラ情報などを表示するための空間を確保するための値．50という値自体に意味はない．
	for (int y = (drawY) / CHIPSIZE; y < ((drawY + window.WINDOW_HEIGHT-50) / CHIPSIZE); y++) {
		for (int x = (drawX) / CHIPSIZE; x < ((drawX + window.WINDOW_WIDTH) / CHIPSIZE); x++) {
			if (y <= MAP_HEIGHT && x <= MAP_WIDTH) {

				int tempX = (x * CHIPSIZE) - drawX;
				int tempY = (y * CHIPSIZE) - drawY;

				//マップチップ代わりの中抜き四角
				//DrawBox(tempX, tempY, tempX + CHIPSIZE, tempY + CHIPSIZE, setColor, false);

				if (1 <= amap[y][x] && amap[y][x] <= 7) DrawGraph(tempX, tempY, chipImg[amap[y][x]], TRUE);
			}
			//主人公の代わりの赤四角
			DrawBox(playerX - drawX, playerY - drawY, playerX + CHIPSIZE * 2 - drawX, playerY + CHIPSIZE * 4 - drawY, GetColor(255, 0, 0), true);
		}
	}





	//for (int y = 0; y < MAP_HEIGHT; y++) {
	//	for (int x = 0; x < MAP_WIDTH; x++) {
	//		drawX = 16 + 16 * x - playerX;
	//		drawY = 16 + 16 * y - playerY;

	//		switch (amap[y][x]) {
	//		case 0:
	//			setColor = GetColor(255, 255, 255);
	//			break;
	//		case 1:
	//			setColor = GetColor(255, 255, 0);
	//			break;
	//		case 2:
	//			setColor = GetColor(120, 120, 120);
	//			break;
	//		case 3:
	//			setColor = GetColor(255, 183, 76);
	//			break;
	//		case 4:
	//			setColor = GetColor(255, 0, 0);
	//			break;
	//		case 5:
	//			setColor = GetColor(228, 212, 161);
	//			break;
	//		case 6:
	//			setColor = GetColor(255, 0, 119);
	//			break;
	//		default:
	//			setColor = GetColor(0, 0, 255);
	//			break;
	//		}
	//		if (50 <= drawX && drawX <= 750 && 50 <= drawY && drawY <= 550) {
	//			DrawBox(drawX, drawY, drawX + 16, drawY + 16, setColor, false);
	//		}
	//	}
	//}
	DrawFormatString(0, 30, GetColor(255, 125, 255), "%d  ,%d", drawX, drawY);
	DrawFormatString(0, 80, GetColor(255, 125, 255), "%d  ,%d", (drawX + window.WINDOW_WIDTH - 100), (drawY + window.WINDOW_HEIGHT - 100));
}


// 仮なのでいつかクラスに分離する
void StageSample::scrollTest() {
	int move = 5;
	if (keyM.GetKeyFrame(KEY_INPUT_UP) >= 1 && playerY - move >= 0) {
		playerY -= move;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN	) >= 1 && playerY + move <= MAP_HEIGHT * 16) {
		playerY += move;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1 && playerX - move >= 0) {
		playerX -= move;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1 && playerX + move <= MAP_WIDTH * 16) {
		playerX += move;
	}
}

// プレイヤーの座標から表示するマップの起点を決定する関数． 2017.8.11 Hilary
void StageSample::scrollMap() {
	if (playerX - 100 >= 0) drawX = playerX - 100;
	else drawX = 0;
	if (playerY - 300 >= 0) drawY = playerY - 300;
	else drawY = 0;
}
