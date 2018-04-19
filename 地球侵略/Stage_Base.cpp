#include "Stage_Base.h"
#include <assert.h>
#include <fstream>
#include <iostream>//�t�@�C�����o��
#include <string>
#include <sstream> //�����X�g���[��
#include "KeyManager.h"
#include "SoundManager.h"
#include "SceneManager.h"

Stage_Base::Stage_Base() {}

Stage_Base::Stage_Base(int stage) {
	stageId = stage;
	SoundM.SetSound(LoadSoundMem("data/mc/�r���̉���A�댯���킸.wav"));

	//�}�b�v�n�`�̓ǂݍ���
	//�����𕡐��X�e�[�W�p�ɏ�������
	readMap("data/map/stage0.csv");
	objectMgr = new ObjectManager(vmap, stageId);
	//�v���C���[�Ăяo��
	this->player = objectMgr->getPlayer();


	//�������� ttp://nanoappli.com/blog/archives/3229
	time = 180'000;
	//DX���C�u�����̋@�\�ł͂Ȃ�C++�̋@�\�Ŏ���������
	//���݁C�ꎞ��~�Ƃ����S�ɖ������Ď��Ԃ��i��
	timeLimit = GetNowCount() + time;

	//�n�`�摜�̓ǂݍ���
	//TODO:�X�e�[�W���Ƃ̈���������
	loadImg();
}

Stage_Base::~Stage_Base() {
	vmap.clear();
	delete objectMgr;
	InitGraph();
}

void Stage_Base::update() {
	//�^�C�}�[
	leftTime = int(timeLimit - GetNowCount());
	if (leftTime <= 0) {
		SceneM.ChangeScene(scene::GameOver);
	}

	drawChipNum = 0;
	objectMgr->update();
	scrollMap();	//�v���C���[���W�ɉ������\���͈͂̕ύX
}

void Stage_Base::draw() {
	DrawGraphF(((800 - bgWidth) *((drawX) / (float)(MAP_WIDTH*CHIPSIZE))), -200, bgHand, false);	//�w�i�̕`��
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

	//�f�o�b�O���
//d	DrawFormatString(0, 30, GetColor(255, 125, 255), "�}�b�v�\�����_�F%d  ,%d", drawX, drawY);
//d	DrawFormatString(0, 50, GetColor(255, 125, 255), "�\���摜���F%d", drawChipNum);
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
	std::ifstream ifs(file);	//�t�@�C���̃I�[�v��
	if (!ifs) return -1;

	while (getline(ifs, str)) {
		std::vector<int> splited;
		std::istringstream stream(str);
		while (getline(stream, buf, ',')) {
			if (buf.size() != 0) {
				temp = std::stoi(buf);		//int�^�ɕύX
			}
			else {
				temp = 0;
			}
			splited.push_back(temp);
		}
		vmap.push_back(splited);
	}
	MAP_WIDTH = vmap[0].size();	//�}�b�v���̑�\�Ƃ��Ĉ�ԍŏ����i�[
	MAP_HEIGHT = vmap.size();

	ifs.close();
	return 1;
}

//�������Ȃ̂Ō�ŕ���
int Stage_Base::loadImg() {
	//�摜�̐ݒ�
	chipImg[2] = LoadGraph("data/img/groundFloor.png");
	chipImg[7] = LoadGraph("data/img/airFloor.png");
	bgHand = LoadGraph("data/img/bg_factory.png");
	int t;
	GetGraphSize(bgHand, &bgWidth, &t);

	//InfoArea�p
	img_hpbar = LoadGraph("data/img/hpbar.png");
	img_hpbar_empty = LoadGraph("data/img/hpbar_empty.png");


	return 1;
}

int Stage_Base::drawInfo() {
	//�w�i ���̂����摜�ɂȂ邩�H
	DrawBox(infoX, infoY, 800, 600, 0x878773, TRUE);
	//HP�\���� MAX15�܂�
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
	//�������ԕ\����
	DrawFormatString(infoX + 300, infoY + 50, 0xFFFFFF, "�c�莞��  %02d:%02d'%02d", leftTime / 60000/*��*/, (leftTime % 60000) / 1000/*�b*/, ((leftTime % 60000) % 1000) / 10 /*ms*/);
	return 0;
}
