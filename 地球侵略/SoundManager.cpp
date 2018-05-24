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
}

void SoundManager::SetSound(int bgm) {					//SetSound(LoadSoundMem("File")
	StopSoundMem(this->bgm);
	DeleteSoundMem(this->bgm);		//��Еt���͑厖�D������Ȃ��ƃ��������[�N�̌����ɂȂ�D
	SoundManager::bgm = bgm;
	ChangeVolumeSoundMem(bgmVolume, SoundManager::bgm);
}

void SoundManager::SoundVolume(int number) {
	if (number == 0) {
		volume = &bgmVolume;
		sound = &bgm;
		bool isVolChanged = false;
		if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
			*volume = ((*volume)++ < 255) ? (*volume)++ : 255;//���ʂ��グ��.Max255
			isVolChanged = true;
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
			*volume = ((*volume)-- > 0) ? (*volume)-- : 0;//���ʂ�������.Min0
			isVolChanged = true;
		}
		if (isVolChanged) {
			ChangeVolumeSoundMem(*volume, *sound);				//��������̉��ʕύX
			isVolChanged = false;
		}
	}
	else {
		volume = &seVolume;
		sound = &se;
		bool isVolChanged = false;
		if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) >= 1) {
			*volume = ((*volume)++ < 255) ? (*volume)++ : 255;//���ʂ��グ��.Max255
			isVolChanged = true;
		}
		else if (keyM.GetKeyFrame(KEY_INPUT_LEFT) >= 1) {
			*volume = ((*volume)-- > 0) ? (*volume)-- : 0;//���ʂ�������.Min0
			isVolChanged = true;
		}
		if (isVolChanged) {
			Se(LoadSoundMem("data/mc/pick up.wav"));
			isVolChanged = false;
		}
	}
}

int SoundManager::Volume(int number) {
	if (number == 0) {
		return bgmVolume;
	}
	else {
		return seVolume;
	}
}
void SoundManager::SoundPlayer() {
	if (CheckSoundMem(bgm) == 0) {
		PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, TRUE);
	}
}

void SoundManager::Se(int se) {								//Se(LoadSoundMem("File")
	ChangeVolumeSoundMem(SoundManager::seVolume, se);
	PlaySoundMem(se, DX_PLAYTYPE_BACK, TRUE);
}