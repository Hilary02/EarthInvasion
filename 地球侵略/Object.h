#pragma once
/**
��������A�C�e���ȂǁC�X�e�[�W��ɔz�u����郂�m���Ǘ�
�ڍז���
*/
class Object {
public:
	Object();
	Object(int x, int y, int handle);
	~Object();
	virtual void Update();
	virtual void Draw(int drawX, int drawY);

	// �}�b�v�ɂ����Ă̐�΍��W���w�肷��Ƃ��̍��W�ɐݒ�
	void setAbsolutePos(int modX, int modY);
	//�ړ��ʂ�ݒ肷��ƈ����̒l���ړ������ʒu�ֈړ�
	void setRelativePos(int modX, int modY);

protected:
	int x, y;

	int imgHundle;
};
