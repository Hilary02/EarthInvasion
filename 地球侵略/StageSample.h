#pragma once

#include <vector>
#include "DxLib.h"
#include "IOcsv.h"

class StageSample
{
public:
	StageSample();
	~StageSample();
	
	int initMap();	//�}�b�v�̏�������ǂݍ���
	void drawMap();	//�}�b�v�̕`��

private:
	const int MAP_HEIGHT;	//�c�����}�b�v�`�b�v��
	const int MAP_WIDTH;	//�������}�b�v�`�b�v��
	const int CHIPSIZE = 16;//�}�b�v�`�b�v�̑傫��
	std::vector<std::vector <int>> vmap;
	//std::vector<int> map;
	//���߂���
	int amap[60][234];
	int* p_map;

	//�폜�\��
	int relativeX=0;
	int relativeY=0;

public:
	// ���Ȃ̂ł����N���X�ɕ�������
	void scrollTest();

private:
	int mapX;
	int mapY;

	//�}�b�v�`�b�v�i�[�p�z��
	int chipImg[10];

	//���쐬:�v���C���[�̍��W
	int playerX;
	int playerY;

	//�}�b�v��`�悷��ۂ̍�����W
	int drawX;
	int drawY;

public:
	// �v���C���[�̍��W����\������}�b�v�̋N�_�����肷��֐��D
	void scrollMap();
};

