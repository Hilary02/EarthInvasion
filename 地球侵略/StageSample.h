#pragma once

#include <vector>
#include "DxLib.h"
#include "IOcsv.h"

class StageSample
{
public:
	StageSample();
	~StageSample();
	int initMap();
	void drawStage();
private:
	const int MAP_HEIGHT;
	const int MAP_WIDTH;
	//std::vector<std::vector <int>> map;
	std::vector<int> map;
	//���߂���
	int amap[60][234];
	int* p_map;

	int relativeX=0;
	int relativeY=0;
public:
	// ���Ȃ̂ł����N���X�ɕ�������
	void scrollTest();
	char key[256];
private:
	int mapX;
	int mapY;

	//�}�b�v�`�b�v�i�[�p�z��
	int chipImg[10];

	//���쐬:�v���C���[�̍��W
	int playerX;
	int playerY;
public:
	// �v���C���[�̍��W����\������}�b�v�̋N�_�����肷��֐��D
	void scrollMap();
};

