#include "StageSample.h"
#include "WindowData.h"
#include "KeyManager.h"

#include "Player.h"

#include <assert.h>

int bgHand;

StageSample::StageSample() :
	//�}�b�v�T�C�Y�ƃv���C���[�̏����ʒu���w��
	MAP_HEIGHT(30)
	, MAP_WIDTH(128)
	, playerX(400)
	, playerY(700)
{
	//08.18�@vector�̃T�C�Y�𓮓I�ɕύX�ł���悤�ɂ���
	//�w�肵���}�b�v�T�C�Y�Ŕz����m��
	//�Q�l�ɂ����Ƃ���
	//http://d.hatena.ne.jp/tei3344/20130207/1360238838

	assert(MAP_HEIGHT >= 0);
	vmap.resize(MAP_HEIGHT);
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			vmap[i].push_back(j);
		}
	}
	player = new Player(vmap);
	player->setAbsolutePos(400, 700);
}

StageSample::~StageSample()
{
}

int StageSample::initMap() {
	IOcsv::CSVtoVector("data/map/tutrial-map���ǔ�32.csv", vmap, MAP_WIDTH, MAP_HEIGHT);

	//�摜�̐ݒ�
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
	return 0;
}


void StageSample::drawMap() {
	//�w�i
	DrawGraph(0, 0, bgHand, false);
	//�f�o�b�O�p�J�E���^
	int drawPics = 0;

	scrollMap();	//�v���C���[���W�ɉ������\���͈͂̕ύX

	// -50�̓L�������Ȃǂ�\�����邽�߂̋�Ԃ��m�ۂ��邽�߂̒l�D50�Ƃ����l���̂ɈӖ��͂Ȃ��D
	int ty = max(0, drawY - CHIPSIZE * 2);
	int tx = max(0, drawX - CHIPSIZE * 2);
	for (int y = ty / CHIPSIZE; y < ((drawY + window.WINDOW_HEIGHT - 50) / CHIPSIZE); y++) {
		for (int x = tx / CHIPSIZE; x < ((drawX + CHIPSIZE + window.WINDOW_WIDTH) / CHIPSIZE); x++) {
			if (y < MAP_HEIGHT && x < MAP_WIDTH) {

				int tempX = (x * CHIPSIZE) - drawX;
				int tempY = (y * CHIPSIZE) - drawY;

				//�}�b�v�`�b�v����̒������l�p
				//DrawBox(tempX, tempY, tempX + CHIPSIZE, tempY + CHIPSIZE, setColor, false);

				if (1 <= vmap[y][x] && vmap[y][x] <= 8) {
					DrawGraph(tempX, tempY, chipImg[vmap[y][x]], TRUE);
					drawPics++;
				}

				if (vmap[y][x] == 9) {
					DrawGraph(tempX, tempY + 16, chipImg[vmap[y][x]], TRUE);
					drawPics++;
				}
				//�󔒕\��
				//else DrawBox(tempX, tempY, tempX + CHIPSIZE, tempY + CHIPSIZE, GetColor(0, 255, 0), FALSE);
			}
			//��l���̑���̐Ԏl�p
			//�}�b�v���W�ƕ`�挴�_����`������Ă��邽�߁C�J�����݂̂̃X�N���[�����\
			DrawBox(playerX - drawX, playerY - drawY, playerX + CHIPSIZE * 2 - drawX, playerY + CHIPSIZE * 2 - drawY, GetColor(255, 0, 0), true);
		}
	}

	//�f�o�b�O���
	DrawFormatString(0, 30, GetColor(255, 125, 255), "�}�b�v�\�����_�F%d  ,%d", drawX, drawY);
	DrawFormatString(0, 50, GetColor(255, 125, 255), "�\���摜���F%d", drawPics);
	player->Update();
	player->Draw(drawX, drawY);
	DrawBox( 0, window.WINDOW_HEIGHT - 80,  window.WINDOW_WIDTH, window.WINDOW_HEIGHT, 0x00FF00, true);
}


// ���Ȃ̂ł����N���X�ɕ�������
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

// �v���C���[�̍��W����\������}�b�v�̋N�_�����肷��֐��D8.11 Hilary
//�v���C���[�̕\���ʒu���Ȃ�炩�̕ϐ��ɓ���Ă�������
void StageSample::scrollMap() {
	//�œK�����Ă����͂�
	int baseDrawX = playerX - 100;
	int baseDrawY = playerY - 300;
	int limitDrawX = MAP_WIDTH * CHIPSIZE - window.WINDOW_WIDTH;
	int limitDrawY = MAP_HEIGHT* CHIPSIZE - window.WINDOW_HEIGHT + 150;

	drawX = min(max(0, baseDrawX), limitDrawX);
	drawY = min(max(0, baseDrawY), limitDrawY);
}
