#pragma once
#include "Scene_Frame.h"
enum Stype {
	BGM,SE
};

class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	void SetSound(int bgm);
	void SoundVolume(Stype num);
	int Volume(int number);
	void SoundPlayer();
	void Se(int se);
private:
	// ���y�n���h��
	int bgm;
	int se;
	int *sound;
	// ����
	int bgmVolume = 255;
	int seVolume = 255;
	int *volume;

	//11�i�K���ʂ�255�i�K�ɕϊ�����DX���C�u������
	void myChangeVolumeSoundMem(int VolumePal, int SoundHandle);
};


extern SoundManager SoundM;