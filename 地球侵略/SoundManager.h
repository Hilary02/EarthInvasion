#pragma once
#include "Scene_Frame.h"
class SoundManager
{
public:
	SoundManager();
	~SoundManager();
	void SetSound(int bgm);
	void SoundVolume(int number);
	int Volume(int number);
	void SoundPlayer();
	void Se(int se);
private:
	// ‰¹Šyƒnƒ“ƒhƒ‹
	int bgm;
	int se;
	int *sound;
	// ‰¹—Ê
	int bgmVolume = 255;
	int seVolume = 255;
	int *volume;
};


extern SoundManager SoundM;