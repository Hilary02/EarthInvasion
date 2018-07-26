#pragma once
#include <vector>
#include <array>
#include "DxLib.h"
#include "WindowData.h"
#include "ObjectManager.h"
#include "SaveData.h"
#include "IStageBase.h"

/**
Stage�N���X�͂܂��n�`��ǂݍ��ށD
Player�N���X�CObjectManager�N���X�Ɏ�l���̈ړ��Ƃ���ȊO�̏����𓊂���̂�
���̃N���X�̓}�b�v���W�ƕ`����W�̕ϊ��������ɒS������

�}�b�v�`�b�v�̃f�[�^��1-9�ő���Ă��邽�߁C20�Ԉȍ~��p���ēG���̕ۑ��Ƃ��ł��邩������Ȃ��D
�ʃt�@�C���ł��Ǘ����ł��邪�C�}�b�v���W�������������ׂȂ���ł��Ȃ���΂����Ȃ��Ȃ�D
*/
class Stage_Base :
	public IStageBase {
public:
	Stage_Base();
	Stage_Base(int stage);
	~Stage_Base();

	void update();	//�X�V����
	void draw();	//�`�揈��
	void scrollMap();	// �v���C���[�̍��W����\������}�b�v�̋N�_�����肷��֐��D

	/*0�Ȃ�Q�[���I�[�o�[�A1�Ȃ�N���A ���̂����������� */
	void PlayAnimation(int type);

private:
	int readStageData(int id);
	int readSummary(std::string file);
	int readMap(std::string file);
	int loadImg();
	int drawInfo();

	int MAP_HEIGHT;	//�c�����}�b�v�`�b�v��
	int MAP_WIDTH;	//�������}�b�v�`�b�v��
	const int CHIPSIZE = 32;//�}�b�v�`�b�v�̑傫��

	int chipImg[10];		//�}�b�v�`�b�v�i�[�p�z��
	int bgHand;				//�w�i�摜�i�[�z��
	int bgWidth;

	int chipsetId;
	int bgmId;
	int playerX;
	int playerY;
	int time;

	int lockdoor[3];        //�h�A�p�i�[�z��
	int moveground[2];      //�������p�z��

	std::vector<std::vector <int>> vmap;	//�}�b�v�f�[�^�i�[

	Player *player;
	ObjectManager *objectMgr;
	SaveData &savedata = SaveData::get_instance();

	//�n�`�Ȃǂ�`�悷��ۂ̍�����W
	int drawX, drawY;

	//���\���G���A�̌��_
	int infoX = 0;
	int infoY = 520;
	int img_hpbar;
	int img_hpbar_empty;
	int hpbar_width = 8;
	int hpbar_height = 16;
	int stageId; //�Z�[�u�p

	//�������ԁi�j

	LONGLONG timeLimit;
	int leftTime;

	//�f�o�b�O�p�f�[�^
	int drawChipNum = 0;

	//�A�j���Đ��t���O
	bool isClearAnimation = false;
	bool isDeadAnimation = false;
	int animationCounter = 0;
	int img_clear;
};