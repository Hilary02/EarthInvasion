#pragma once

enum class ObjectID {
	none = 0, //�����Ȃ����
	inVisibleWall = 1, //�����Ȃ���
	ground = 2, //�n��
	colorDifGround = 3, //�F�Ⴂ�n��
	spike = 4,		//�Ƃ��Ƃ�
	reverseSpike = 5, //�t�Ƃ�
	spark = 6, //�r���r��
	fire = 7, //��
	abyss = 9, //�ޗ��i�����j

	moveingFloor = 10,//������

	difMoveGround = 11,//�t�����ɓ����n�ʁi���j
	lockedDoor = 12,	//���Ă����
	alienLaser = 13, //�G�C���A�����[�U�[

	soldierA = 20,	//��ʕ��m
	ltv = 21,  //����
	soldierB = 22, //�x�e������
	venomMan = 23, //�Ől��
	caster = 24, //���@�g��

	healPot = 30,	//�񕜃A�C�e��
	detoxificationPot = 31, //��Ŗ�

	goal = 99,		//�S�[��
	playerBullet = 100,	//�v���C���[���������e
	enemyBullet = 104,	//���m���������e
};