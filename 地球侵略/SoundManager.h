#pragma once
#include "Scene_Frame.h"
#include <unordered_map>
#include <String>

enum Stype {
	BGM, SE
};

class SoundManager {
public:
	SoundManager();
	~SoundManager();
	void SetMusic(int bgm,bool loopFlag = true);
	void SoundVolume(Stype num);
	int Volume(int number);
	void SoundPlayer();
	void Se(int handle);
	void Se(std::string path);
private:
	// ���y�n���h��
	int bgm;
	int se;
	int *sound;
	// ����
	int bgmVolume = 255;
	int seVolume = 255;
	int *volume;
	std::unordered_map<std::string, int> seCache;

	//11�i�K���ʂ�255�i�K�ɕϊ�����DX���C�u������
	void myChangeVolumeSoundMem(int VolumePal, int SoundHandle);
};


extern SoundManager SoundM;