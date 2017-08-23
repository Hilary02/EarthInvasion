#include "StageSample.h"
#include "WindowData.h"
#include "KeyManager.h"

StageSample::StageSample() :
	//�}�b�v�T�C�Y�ƃv���C���[�̏����ʒu���w��
	MAP_HEIGHT(60)
	, MAP_WIDTH(234)
	, playerX(3100)
	, playerY(800)
{
	/*
	//08.18�@vector�̃T�C�Y�𓮓I�ɕύX�ł���悤�ɂ���
	//�w�肵���}�b�v�T�C�Y�Ŕz����m��
	//�Q�l�ɂ����Ƃ���
	//http://d.hatena.ne.jp/tei3344/20130207/1360238838
	*/

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
	//�f�o�b�O�p�J�E���^
	int drawPics = 0;

	scrollMap();	//�v���C���[���W�ɉ������\���͈͂̕ύX


	// -50�̓L�������Ȃǂ�\�����邽�߂̋�Ԃ��m�ۂ��邽�߂̒l�D50�Ƃ����l���̂ɈӖ��͂Ȃ��D
	for (int y = (drawY) / CHIPSIZE; y < ((drawY + window.WINDOW_HEIGHT-50) / CHIPSIZE); y++) {
		for (int x = (drawX) / CHIPSIZE; x < ((drawX + window.WINDOW_WIDTH) / CHIPSIZE); x++) {
			if (y < MAP_HEIGHT && x < MAP_WIDTH) {

				int tempX = (x * CHIPSIZE) - drawX;
				int tempY = (y * CHIPSIZE) - drawY;

				//�}�b�v�`�b�v����̒������l�p
				//DrawBox(tempX, tempY, tempX + CHIPSIZE, tempY + CHIPSIZE, setColor, false);

			//	if (1 <= amap[y][x] && amap[y][x] <= 7) DrawGraph(tempX, tempY, chipImg[amap[y][x]], TRUE);
				if (1 <= vmap[y][x] && vmap[y][x] <= 7) {
					DrawGraph(tempX, tempY, chipImg[vmap[y][x]], TRUE);
					drawPics++;
				}
				//�󔒕\��
				//else DrawBox(tempX, tempY, tempX + CHIPSIZE, tempY + CHIPSIZE, GetColor(0, 255, 0), FALSE);
			}
			//��l���̑���̐Ԏl�p
			//�}�b�v���W�ƕ`�挴�_����`������Ă��邽�߁C�J�����݂̂̃X�N���[�����\
			DrawBox(playerX - drawX, playerY - drawY, playerX + CHIPSIZE  - drawX, playerY + CHIPSIZE * 2 - drawY, GetColor(255, 0, 0), true);
		}
	}

	//�f�o�b�O���
	DrawFormatString(0, 30, GetColor(255, 125, 255), "�}�b�v�\�����_�F%d  ,%d", drawX, drawY);
	DrawFormatString(0, 50, GetColor(255, 125, 255), "�\���摜���F%d", drawPics);
}


// ���Ȃ̂ł����N���X�ɕ�������
void StageSample::scrollTest() {
	int move = 5;
	if (keyM.GetKeyFrame(KEY_INPUT_UP) >= 1 && playerY - move >= 0) {
		playerY -= move;
	}
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN	) >= 1 && playerY + move <= MAP_HEIGHT * CHIPSIZE) {
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


	//���[
	drawX = (playerX - 100 >= 0) ? playerX - 100 : 0;
	//�E�[
	if(playerX + window.WINDOW_WIDTH -100 >= MAP_WIDTH * CHIPSIZE) drawX= MAP_WIDTH * CHIPSIZE -window.WINDOW_WIDTH;
	//��[
	drawY = (playerY - 300 >= 0) ? playerY - 300 : 0;
	//���[
	if (playerY + window.WINDOW_HEIGHT -450 >= MAP_HEIGHT * CHIPSIZE) drawY = MAP_HEIGHT* CHIPSIZE - window.WINDOW_HEIGHT + 150;
}
