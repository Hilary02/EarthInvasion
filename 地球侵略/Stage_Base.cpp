#include "Stage_Base.h"
#include <assert.h>
#include <fstream>
#include <iostream>//�t�@�C�����o��
#include <string>
#include <sstream> //�����X�g���[��
#include <vector>
#include "SoundManager.h"

Stage_Base::Stage_Base() :
	//�R���X�g���N�^�̈����ɐݒ肳��Ȃ��Ƃ����Ȃ�
	MAP_HEIGHT(30)
	, MAP_WIDTH(128) {
	SoundM.SetSound(LoadSoundMem("data/mc/�r���̉���A�댯���킸.wav"));
	//08.18�@vector�̃T�C�Y�𓮓I�ɕύX�ł���悤�ɂ���
	//�w�肵���}�b�v�T�C�Y�Ŕz����m��
	//�Q�l�ɂ����Ƃ���
	//http://d.hatena.ne.jp/tei3344/20130207/1360238838

	//�}�b�v�̗̈�̊m��
	assert(MAP_HEIGHT >= 0);
	assert(MAP_WIDTH >= 0);
	vmap.resize(MAP_HEIGHT);
	for (int i = 0; i < MAP_HEIGHT; i++) {
		for (int j = 0; j < MAP_WIDTH; j++) {
			vmap[i].push_back(j);
		}
	}
	//�}�b�v�n�`�̓ǂݍ���
	readMap("data/map/tutrial-map���ǔ�32.csv");
	//�v���C���[�Ăяo��
	player = new Player(vmap);
	player->setAbsolutePos(360, 600);
	//�n�`�摜�̓ǂݍ���
	//TODO:����������
	loadImg();
}


Stage_Base::~Stage_Base() {
	delete player;
}

void Stage_Base::update() {
	totalFrame++;
	drawChipNum = 0;
	player->Update();
	scrollMap();	//�v���C���[���W�ɉ������\���͈͂̕ύX
}

void Stage_Base::draw() {
	//DrawGraph(0, 0, bgHand, false);	//�w�i�̕`��
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
	//�f�o�b�O���
	DrawFormatString(0, 30, GetColor(255, 125, 255), "�}�b�v�\�����_�F%d  ,%d", drawX, drawY);
	DrawFormatString(0, 50, GetColor(255, 125, 255), "�\���摜���F%d", drawChipNum);
}


void Stage_Base::scrollMap() {
	//TODO:�����͂�����const�ϐ��ɂ���
	int baseDrawX = player->getX() - 100;
	int baseDrawY = player->getY() - 300;
	int limitDrawX = MAP_WIDTH * CHIPSIZE - window.WINDOW_WIDTH;
	int limitDrawY = MAP_HEIGHT* CHIPSIZE - window.WINDOW_HEIGHT + 150;

	drawX = min(max(0, baseDrawX), limitDrawX);
	drawY = min(max(0, baseDrawY), limitDrawY);
}

int Stage_Base::readMap(std::string file) {
	std::string str;	//�s���i�[
	std::string buf;	//�l���i�[
	int temp;
	//�t�@�C���̃I�[�v��
	std::ifstream ifs(file);
	if (!ifs) return 1;

	for (int y = 0; y < this->MAP_HEIGHT; y++) {
		getline(ifs, str);				//csv�t�@�C����1�s�ǂݍ���
		std::istringstream stream(str);
		for (int x = 0; x < this->MAP_WIDTH; x++) {
			getline(stream, buf, ',');	//�J���}�ŋ�؂�
			if (buf.size() != 0) {
				temp = std::stoi(buf);		//int�^�ɕύX
			}
			else {
				temp = 0;
			}

			this->vmap[y][x] = temp;			//vector���A�N�Z�X���@�͔z��Ɠ��l�ɍs����
		}
	}
	return 1;
}

//�������Ȃ̂Ō�ŕ���
int Stage_Base::loadImg() {
	//�摜�̐ݒ�
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