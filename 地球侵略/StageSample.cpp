#include "StageSample.h"
#include "WindowData.h"
#include "KeyManager.h"

StageSample::StageSample() :
	MAP_HEIGHT(60)
	, MAP_WIDTH(234)
	, playerX(100)
	, playerY(800)
{
	vmap.resize(MAP_HEIGHT);
	for (int i = 0; i<MAP_HEIGHT; i++){
		for (int j = 0; j<MAP_WIDTH; j++){
			vmap[i].push_back(j);
		}
	}
}


StageSample::~StageSample()
{
}

int StageSample::initMap() {
	p_map = &amap[0][0];
	IOcsv::ReadMap("data/map/�`���[�g���A���}�b�v.csv", &amap[0][0], MAP_WIDTH, MAP_HEIGHT);
	IOcsv::CSVtoVector("data/map/�`���[�g���A���}�b�v.csv", vmap, MAP_WIDTH, MAP_HEIGHT);

	LoadDivGraph("data/img/mapchip10.png", 10, 10, 1, 16, 16, chipImg);
	return 0;

}


void StageSample::drawMap() {
	int setColor = GetColor(125, 125, 125);

	scrollMap();	//�v���C���[���W�ɉ������\���͈͂̕ύX
	

	for (int i = 0; i < 10; i++) {
		DrawGraph(100 + i * 16, 100, chipImg[i], true);
	}

	// -50�̓L�������Ȃǂ�\�����邽�߂̋�Ԃ��m�ۂ��邽�߂̒l�D50�Ƃ����l���̂ɈӖ��͂Ȃ��D
	for (int y = (drawY) / CHIPSIZE; y < ((drawY + window.WINDOW_HEIGHT-50) / CHIPSIZE); y++) {
		for (int x = (drawX) / CHIPSIZE; x < ((drawX + window.WINDOW_WIDTH) / CHIPSIZE); x++) {
			if (y < MAP_HEIGHT && x < MAP_WIDTH) {

				int tempX = (x * CHIPSIZE) - drawX;
				int tempY = (y * CHIPSIZE) - drawY;

				//�}�b�v�`�b�v����̒������l�p
				//DrawBox(tempX, tempY, tempX + CHIPSIZE, tempY + CHIPSIZE, setColor, false);

			//	if (1 <= amap[y][x] && amap[y][x] <= 7) DrawGraph(tempX, tempY, chipImg[amap[y][x]], TRUE);
				if (1 <= vmap[y][x] && vmap[y][x] <= 7) DrawGraph(tempX, tempY, chipImg[vmap[y][x]], TRUE);
				else DrawBox(tempX, tempY, tempX + CHIPSIZE, tempY + CHIPSIZE, GetColor(0, 255, 0), FALSE);
			}
			//��l���̑���̐Ԏl�p
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


// ���Ȃ̂ł����N���X�ɕ�������
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

// �v���C���[�̍��W����\������}�b�v�̋N�_�����肷��֐��D 2017.8.11 Hilary
void StageSample::scrollMap() {
	if (playerX - 100 >= 0) drawX = playerX - 100;
	else drawX = 0;
	if (playerY - 300 >= 0) drawY = playerY - 300;
	else drawY = 0;
}
