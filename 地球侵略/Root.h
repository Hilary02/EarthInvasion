#pragma once
class Root
{
public:
	Root();
	~Root();

private:
	// ���W
	double defaultX;
	double defaultY;
	double x;
	double y;
public:
	// �}�b�v�ɂ����Ă̐�΍��W���w�肷��Ƃ��̍��W�ɐݒ�
	void setPos(double modX, double modY);
};

