#include "SaveData.h"
//#include <iostream>//�t�@�C�����o��
#include <fstream>

#include <iostream>
using namespace std;

SaveData & SaveData::get_instance() {
	static SaveData instance;
	return instance;
}

int SaveData::makeSave() {
	content.bgmVolume = 200;
	content.seVolume = 200;
	content.clearFlag[0] = 2;
	return 0;
}

int SaveData::save() {
	std::ofstream ofs("save.dat", std::ios::binary);
	if (!ofs) return -1;
	ofs.write((char*)&content, sizeof(content));
	ofs.close();
	return 0;
}

int SaveData::load() {
	std::ifstream ifs("save.dat", std::ios::binary);
	if (!ifs) return -1;
	ifs.read((char*)&content, sizeof(content));
	ifs.close();
	return 0;
}

void SaveData::d_print() {
	cout << content.bgmVolume << ",";
	cout << content.seVolume << ",";
	for (int i : content.clearFlag)
		cout << i << flush;
	cout << endl;
}

int SaveData::getBGMVol() { return content.bgmVolume; }
int SaveData::getSEVol() { return content.seVolume; }
int SaveData::getClearFlag(int stage) { return content.bgmVolume; }
void SaveData::setBGMVol(int vol) { content.bgmVolume = vol; }
void SaveData::setSEVol(int vol) { content.seVolume = vol; }
void SaveData::setClearFlag(int stage, int flag) { content.clearFlag[stage] = flag; }

SaveData::SaveData() {}
SaveData::~SaveData() {}