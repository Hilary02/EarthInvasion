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
	//�}�b�v�n�`�̓ǂݍ���
	//�����𕡐��X�e�[�W�p�ɏ�������
	if (readStageData(stage) == -1) {
		printfDx("Read Error");
	}
	SoundM.SetMusic(LoadSoundMem(bgmPath.c_str()));
	//�n�`�摜�̓ǂݍ���
	//TODO:�X�e�[�W���Ƃ̈���������
	loadImg();
	objectMgr = new ObjectManager(vmap, stageId, this);
	//�v���C���[�Ăяo��
	this->player = objectMgr->getPlayer();
	player->setAbsolutePos(playerX, playerY);
	befX = player->getX();
	befY = player->getY();


	//�������� ttp://nanoappli.com/blog/archives/3229
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
	if (!(isDeadAnimation || isClearAnimation)) { //�ǂ����False ->�A�j���Ȃ��Ȃ�
		//�^�C�}�[
		if (!(SceneM.isPausing)) {
			leftTime -= int(dTime);
		}
		if (leftTime <= 0) {
			SceneM.ChangeScene(scene::GameOver);
		}

		drawChipNum = 0;

		//����ł��N���A���Ă��Ȃ���΃I�u�W�F�N�g���X�V
		if (!isDeadAnimation && !isClearAnimation) {
			objectMgr->update();
		}
		scrollMap();	//�v���C���[���W�ɉ������\���͈͂̕ύX
	}
}

void Stage_Base::draw() {
	//�^�C�}�[
	dTime = (GetNowCount() - beforeTime);
	beforeTime = GetNowCount();


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
	//�`���[�g���A���̂��
	if (stageId == 0) {
		DrawRotaGraph(625, 88, 0.5, 0, img_tutorial, TRUE);
	}
	objectMgr->Draw(drawX, drawY);
	drawInfo();

	if (isClearAnimation) {
		DrawGraph(0, 0, img_clear, true);
		ChangeFontType(DX_FONTTYPE_EDGE);
		DrawString(250, 400, "Z�L�[�ŃZ���N�g��ʂ�", 0xFFFFFF);
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

	//�f�o�b�O���
//d	DrawFormatString(0, 30, GetColor(255, 125, 255), "�}�b�v�\�����_�F%d  ,%d", drawX, drawY);
//d	DrawFormatString(0, 50, GetColor(255, 125, 255), "�\���摜���F%d", drawChipNum);
}


void Stage_Base::scrollMap() {
	//�v���C���[�̌����ɉ����Ď��E��ω�
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

//�����ƃX�}�[�g�ȕ��@�Ȃ����ȁH
int Stage_Base::readStageData(int stage) {
	std::string first = "data/stagedata/";
	std::string type = "summary";
	std::string id = std::to_string(stage);	//������id��
	std::string csv = ".csv";

	std::string path = first + type + id + csv;
	if (readSummary(path) == -1) return -1;

	type = "map";
	path = first + type + id + csv;
	if (readMap(path) == -1) return -1;

	return 0;
}

int Stage_Base::readSummary(std::string file) {
	std::string str;	//�s���i�[
	std::string buf;	//�l���i�[
	std::vector<int> splited;

	std::ifstream ifs(file);	//�t�@�C���̃I�[�v��
	if (!ifs) return -1;

	getline(ifs, str);	//�擪�s�̓ǂݔ�΂�
	getline(ifs, str);	//2�s�ڂ����ǂ�
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
	MAP_WIDTH = (int)(vmap[0].size());	//�}�b�v���̑�\�Ƃ��Ĉ�ԍŏ����i�[
	MAP_HEIGHT = (int)(vmap.size());

	ifs.close();
	return 1;
}

//�������Ȃ̂Ō�ŕ���
int Stage_Base::loadImg() {
	//�摜�̐ݒ�
	chipImg[2] = LoadGraph("data/img/groundFloor.png");
	chipImg[3] = LoadGraph("data/img/airFloor.png");

	bgHand = LoadGraph(bgPath.c_str());

	int t;
	GetGraphSize(bgHand, &bgWidth, &t);

	//InfoArea�p
	img_hpbar = LoadGraph("data/img/hpbar.png");
	img_hpbar_empty = LoadGraph("data/img/hpbar_empty.png");
	img_tutorial = LoadGraph("data/img/tutorial.png");
	img_clear = LoadGraph("data/img/clear_img.png");
	return 1;
}

int Stage_Base::drawInfo() {
	//�w�i ���̂����摜�ɂȂ邩�H
	DrawBox(infoX, infoY, 800, 600, 0x878773, TRUE);
	//HP�\���� MAX15�܂�
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
	//�������ԕ\����
	DrawFormatString(infoX + 300, infoY + 50, 0xFFFFFF, "�c�莞��  %02d:%02d'%02d", leftTime / 60000/*��*/, (leftTime % 60000) / 1000/*�b*/, ((leftTime % 60000) % 1000) / 10 /*ms*/);
	return 0;
}
