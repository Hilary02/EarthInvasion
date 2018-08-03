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
	void SetSound(int bgm);
	void SoundVolume(Stype num);
	int Volume(int number);
	void SoundPlayer();
	void Se(int handle);
	void Se(std::string path);
private:
	// 音楽ハンドル
	int bgm;
	int se;
	int *sound;
	// 音量
	int bgmVolume = 255;
	int seVolume = 255;
	int *volume;
	std::unordered_map<std::string, int> seCache;

	//11段階音量を255段階に変換してDXライブラリに
	void myChangeVolumeSoundMem(int VolumePal, int SoundHandle);
};


extern SoundManager SoundM;