#pragma once

#include <vector>
#include "DxLib.h"
#include "IOcsv.h"
#include "Player.h"
/**
�ύX�K�v�ȂƂ��둽���D
�}�b�v�`�b�v�T�C�Y�̕ύX��N���X����

��l���̈ړ���Stage�N���X�ŊǗ������Ă������̂�������Ȃ�
�G�̏��i�[�z��C�A�C�e���̔z��D�D�D�̂悤�Ɋe�I�u�W�F�N�g���ɊǗ��z����쐬���C
�|�C���^��p���ăA�N�Z�X�ł���΃X�e�[�W���ɏ_��ȃX�e�[�W�쐬���s����ƍl����D

���݁C�L�����N�^�̍��W���}�b�v�S�̂̍��W�ŊǗ����ł��Ă���D

�}�b�v�`�b�v�̃f�[�^��1-9�ő���Ă��邽�߁C20�Ԉȍ~��p���ēG���̕ۑ��Ƃ��ł��邩������Ȃ��D
�ʃt�@�C���ł��Ǘ����ł��邪�C�}�b�v���W�������������ׂȂ���ł��Ȃ���΂����Ȃ��Ȃ�D


*/ 
class StageSample
{
public:
	StageSample();
	~StageSample();
	
	int initMap();	//�}�b�v�̏�������ǂݍ���
	void drawMap();	//�}�b�v�̕`��

	// ���Ȃ̂ł����N���X�ɕ�������
	void scrollTest();
	void scrollMap();	// �v���C���[�̍��W����\������}�b�v�̋N�_�����肷��֐��D

private:
	const int MAP_HEIGHT;	//�c�����}�b�v�`�b�v��
	const int MAP_WIDTH;	//�������}�b�v�`�b�v��
	const int CHIPSIZE = 32;//�}�b�v�`�b�v�̑傫��
	
	int chipImg[10];		//�}�b�v�`�b�v�i�[�p�z��

	int lockdoor[3];        //�h�A�p�i�[�z��
	int moveground[2];      //�������p�z��

	std::vector<std::vector <int>> vmap;	//�}�b�v�f�[�^�i�[
	Player player;

private:
	//�폜�\��
	int mapX;
	int mapY;


	//���쐬:�v���C���[�̍��W
	int playerX;
	int playerY;

	//�`�悷��ۂ̍�����W
	int drawX;
	int drawY;
	
};

