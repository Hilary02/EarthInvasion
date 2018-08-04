#include "SoundManager.h"
#include "SaveData.h"

SoundManager SoundM;

SoundManager::SoundManager() {
	SaveData::get_instance().load();
	bgmVolume = SaveData::get_instance().getBGMVol();
	seVolume = SaveData::get_instance().getSEVol();
}

SoundManager::~SoundManager() {
	SaveData::get_instance().setBGMVol(bgmVolume);
	SaveData::get_instance().setSEVol(seVolume);
	SaveData::get_instance().save();
	DeleteSoundMem(bgm);
	DeleteSoundMem(se);
	seCache.clear();
}

void SoundManager::SetSound(int bgm) {					//SetSound(LoadSoundMem("File")
	StopSoundMem(this->bgm);
	DeleteSoundMem(this->bgm);		//��Еt���͑厖�D������Ȃ��ƃ��������[�N�̌����ɂȂ�D
	SoundManager::bgm = bgm;
	myChangeVolumeSoundMem(bgmVolume, SoundManager::bgm);
}

void SoundManager::SoundVolume(Stype num) {
	bool isVolChanged = false;
	if (num == Stype::BGM) {
		volume = &bgmVolume;
		sound = &bgm;
		if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) == 1) {
			*volume = ((*volume)++ < 10) ? (*volume)++ : 10;//���ʂ��グ��.Max10
			isVolChanged = true;
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) == 1) {
			*volume = ((*volume)-- > 0) ? (*volume)-- : 0;//���ʂ�������.Min0
			isVolChanged = true;
		}
	}
	else if (num == Stype::SE) {
		volume = &seVolume;
		sound = &se;
		if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) == 1) {
			*volume = ((*volume)++ < 10) ? (*volume)++ : 10;//���ʂ��グ��.Max10
			isVolChanged = true;
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) == 1) {
			*volume = ((*volume)-- > 0) ? (*volume)-- : 0;//���ʂ�������.Min0
			isVolChanged = true;
		}
	}

	if (isVolChanged) {
		Se("data/mc/pick up.wav");
		myChangeVolumeSoundMem(*volume, *sound);				//��������̉��ʕύX
		isVolChanged = false;
	}
}

int SoundManager::Volume(int number) {
	if (number == 0) { return bgmVolume; }
	else { return seVolume; }
}

void SoundManager::SoundPlayer() {
	if (CheckSoundMem(bgm) == 0) { PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE); }
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
	ChangeVolumeSoundMem(255 * log10(vol), handle);
}
