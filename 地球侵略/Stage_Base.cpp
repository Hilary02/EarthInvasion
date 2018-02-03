#include "Stage_Base.h"
#include <assert.h>
#include <fstream>
#include <iostream>//�t�@�C�����o��
#include <string>
#include <sstream> //�����X�g���[��
#include "KeyManager.h"
#include "SoundManager.h"
#include "SceneManager.h"

Stage_Base::Stage_Base(){}

Stage_Base::Stage_Base(int stage) {
	stageId = stage;
	//�R�[�h��O���t�@�C���ɏ������炢�Ȃ�csv����ǂݎ�����ق������֐��������H
	//Array�ɂ���Ȃ�傫�߂Ɏ���Ă����Ƃ��DVector���ƍL���X�e�[�W�ɂȂ����Ƃ��̓ǂݍ��ݑ��x���S�z�D
	MAP_HEIGHT = 30;
	MAP_WIDTH = 128;
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

	//�����𕡐��X�e�[�W�p�ɏ�������
	readMap("data/map/stage0.csv");

	//�v���C���[�Ăяo��
	player = new Player(vmap);
	player->setAbsolutePos(1800, 600);
	colMgr = new CollisionManager(player);
	objectMgr = new ObjectManager(vmap,player,colMgr,stageId);

	//�ǂ��炩���g��
	//objectMgr = new ObjectManager(vmap,player);

	//�������� ttp://nanoappli.com/blog/archives/3229
	time = 120'000;
	//DX���C�u�����̋@�\�ł͂Ȃ�C++�̋@�\�Ŏ���������
	//���݁C�ꎞ��~�Ƃ����S�ɖ������Ď��Ԃ��i��
	timeLimit = GetNowCount() + time;

	//�n�`�摜�̓ǂݍ���
	//TODO:�X�e�[�W���Ƃ̈���������
	loadImg();
}

Stage_Base::~Stage_Base() {
	vmap.clear();
	delete player;
	delete colMgr;
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
	player->update();
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
	objectMgr->Draw(drawX, drawY);
	player->Draw(drawX, drawY);
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
	ifs.close();
	return 1;
}

//�������Ȃ̂Ō�ŕ���
int Stage_Base::loadImg() {
	//�摜�̐ݒ�
	chipImg[2] = LoadGraph("data/img/groundFloor.png");
	chipImg[7] = LoadGraph("data/img/airFloor.png");
	bgHand = LoadGraph("data/img/bg01.jpg");

	//InfoArea�p
	img_hpbar = LoadGraph("data/img/hpbar.png");
	img_hpbar_empty = LoadGraph("data/img/hpbar_empty.png");


	return 1;
}

int Stage_Base::drawInfo(){
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
	DrawFormatString(infoX+300, infoY+50, 0xFFFFFF, "�c�莞��  %02d:%02d'%02d", leftTime / 60000/*��*/, (leftTime % 60000) / 1000/*�b*/, ((leftTime % 60000) % 1000)/10 /*ms*/);
	return 0;
}
