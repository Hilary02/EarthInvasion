#pragma once
#include <array>
//NOTE: �V���O���g���������Ă݂�
//get_instance���\�b�h������̂��擾

class SaveData {
public:
	static SaveData& get_instance();
	int makeSave();
	int save();
	int load();
	void d_print();	//Debug

	int getBGMVol();
	int getSEVol();
	int getClearFlag(int stage);
	void setBGMVol(int vol);
	void setSEVol(int vol);
	void setClearFlag(int stage, int flag);

private:
	struct content {
		int bgmVolume;
		int seVolume;
		int clearFlag[14];
	};

	SaveData();
	SaveData(const SaveData&) {};
	~SaveData();

	content content;

};