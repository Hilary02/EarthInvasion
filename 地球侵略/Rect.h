#pragma once
class Rect
{
public:
	Rect(int, int, int, int);
	Rect();
	~Rect();
	//������WX�̎擾
	int getLeftX();
	//������WY�̎擾
	int getLeftY();
	//��`�̕����擾
	int getWidth();
	//��`�̍������擾
	int getHeight();
	//�����蔻��
	bool isHit(Rect);
private:
	int leftX, leftY, width, height;



};

