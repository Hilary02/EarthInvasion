#include "SoundManager.h"
#include "SaveData.h"

SoundManager SoundM;

SoundManager::SoundManager() {
	if (SaveData::get_instance().load() == 0) {
		bgmVolume = SaveData::get_instance().getBGMVol();
		seVolume = SaveData::get_instance().getSEVol();
	}
	else {
		bgmVolume = 5;
		seVolume = 5;
	}
}

SoundManager::~SoundManager() {
	SaveData::get_instance().setBGMVol(bgmVolume);
	SaveData::get_instance().setSEVol(seVolume);
	SaveData::get_instance().save();
	DeleteSoundMem(bgm);
	DeleteSoundMem(se);
	seCache.clear();
}

void SoundManager::SetMusic(int bgm, bool loopFlag) {					//SetMusic(LoadSoundMem("File")
	StopSoundMem(this->bgm);
	DeleteSoundMem(this->bgm);		//後片付けは大事．解放しないとメモリリークの原因になる．
	SoundManager::bgm = bgm;
	myChangeVolumeSoundMem(bgmVolume, bgm);
	if (loopFlag) {
		PlaySoundMem(this->bgm, DX_PLAYTYPE_LOOP);
	}
	else {
		PlaySoundMem(bgm, DX_PLAYTYPE_BACK);
	}
}

void SoundManager::SoundVolume(Stype num) {
	bool isVolChanged = false;
	if (num == Stype::BGM) {
		volume = &bgmVolume;
		sound = &bgm;
		if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) == 1) {
			*volume = ((*volume)++ < 10) ? (*volume)++ : 10;//音量を上げる.Max10
			isVolChanged = true;
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) == 1) {
			*volume = ((*volume)-- > 0) ? (*volume)-- : 0;//音量を下げる.Min0
			isVolChanged = true;
		}
	}
	else if (num == Stype::SE) {
		volume = &seVolume;
		sound = &se;
		if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) == 1) {
			*volume = ((*volume)++ < 10) ? (*volume)++ : 10;//音量を上げる.Max10
			isVolChanged = true;
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) == 1) {
			*volume = ((*volume)-- > 0) ? (*volume)-- : 0;//音量を下げる.Min0
			isVolChanged = true;
		}
	}

	if (isVolChanged) {
		Se("data/mc/pick up.wav");
		myChangeVolumeSoundMem(*volume, *sound);				//メモリ上の音量変更
		isVolChanged = false;
	}
}

int SoundManager::Volume(int number) {
	if (number == 0) { return bgmVolume; }
	else { return seVolume; }
}

void SoundManager::SoundPlayer() {
	//	if (CheckSoundMem(bgm) == 0) { PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE); }
}

void SoundManager::Se(int handle) {
	//Se(LoadSoundMem("File");
	myChangeVolumeSoundMem(SoundManager::seVolume, handle);
	PlaySoundMem(handle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::Se(std::string path) {
	auto itr = seCache.find(path);
	int handle;
	if (itr != seCache.end()) {
		handle = itr->second;
	}
	else {
		seCache[path] = LoadSoundMem(path.c_str());
		handle = seCache[path];
	}
	myChangeVolumeSoundMem(SoundManager::seVolume, handle);
	PlaySoundMem(handle, DX_PLAYTYPE_BACK, TRUE);
}

void SoundManager::myChangeVolumeSoundMem(int vol, int handle) {
	ChangeVolumeSoundMem(static_cast<int>(255 * log10(vol)), handle);
}
