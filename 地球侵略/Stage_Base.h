#pragma once


#include "DxLib.h"
#include "Player.h"
#include "WindowData.h"

/**
Stage�N���X�͂܂��n�`��ǂݍ��ށD
Player�N���X�CObjectManager�N���X�Ɏ�l���̈ړ��Ƃ���ȊO�̏����𓊂���̂�
���̃N���X�̓}�b�v���W�ƕ`����W�̕ϊ��������ɒS������

�}�b�v�`�b�v�̃f�[�^��1-9�ő���Ă��邽�߁C20�Ԉȍ~��p���ēG���̕ۑ��Ƃ��ł��邩������Ȃ��D
�ʃt�@�C���ł��Ǘ����ł��邪�C�}�b�v���W�������������ׂȂ���ł��Ȃ���΂����Ȃ��Ȃ�D
*/
class Stage_Base{
public:
	Stage_Base();
	~Stage_Base();

	void update();	//�X�V����
	void draw();	//�`�揈��

					
	void scrollTest();
	void scrollMap();	// �v���C���[�̍��W����\������}�b�v�̋N�_�����肷��֐��D

private:
	int readMap(std::string file);
	int loadImg();
	int debugInfo();


	const int MAP_HEIGHT;	//�c�����}�b�v�`�b�v��
	const int MAP_WIDTH;	//�������}�b�v�`�b�v��
	const int CHIPSIZE = 32;//�}�b�v�`�b�v�̑傫��

	int chipImg[10];		//�}�b�v�`�b�v�i�[�p�z��
	int bgHand;				//�w�i�摜�i�[�z��

	int lockdoor[3];        //�h�A�p�i�[�z��
	int moveground[2];      //�������p�z��

	std::vector<std::vector <int>> vmap;	//�}�b�v�f�[�^�i�[
	Player *player;

	//�`�悷��ۂ̍�����W
	int drawX,drawY;

	int playerX, playerY;
};