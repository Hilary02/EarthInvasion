#pragma once
/**
�}�b�v�ɔz�u����A�C�e����G�ȂǂɕK�v�ȏ����Ǘ�����D

*/
class Root {
public:
	Root();
	~Root();

private:
	//�������W
	double defaultX;
	double defaultY;
	//���ݍ��W
	double x;
	double y;
public:
	// �}�b�v�ɂ����Ă̐�΍��W���w�肷��Ƃ��̍��W�ɐݒ�
	void setAbsolutePos(double modX, double modY);
	//�ړ��ʂ�ݒ肷��ƈ����̒l���ړ������ʒu�ֈړ�
	void setRelativePos(double modX, double modY);
};

