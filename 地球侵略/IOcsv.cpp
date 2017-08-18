#include "IOcsv.h"

IOcsv::IOcsv()
{
}


IOcsv::~IOcsv()
{
}


int IOcsv::CSVtoVector(std::string file, std::vector<std::vector<int> >& vec, int w, int h)
{
	std::string str;	//�s���i�[
	std::string buf;	//�l���ꎞ�i�[
	int temp;
	//�t�@�C���̃I�[�v��
	std::ifstream ifs(file);
	if (!ifs) return 1;

	for (int y = 0; y < h; y++) {
		getline(ifs, str);				//csv�t�@�C����1�s�ǂݍ���
		std::istringstream stream(str);
		for (int x = 0; x < w; x++) {
			getline(stream, buf, ',');	//�J���}�ŋ�؂�
			temp = std::stoi(buf);		//int�^�ɕύX
			vec[y][x] = temp;
		}
	}
	return 0;
}




int IOcsv::ReadMap(char *file, int *data, int w, int h){
	std::string str;	//�s���i�[
	std::string buf;	//�l���ꎞ�i�[
	int temp;
	//�t�@�C���̃I�[�v��
	std::ifstream ifs(file);
	if (!ifs) return 1;


	for (int y = 0; y < h; y++) {		
		getline(ifs, str);				//csv�t�@�C����1�s�ǂݍ���
		std::istringstream stream(str);
		for (int x = 0; x < w; x++) {
			getline(stream, buf, ',');	//�J���}�ŋ�؂�
			temp = std::stoi(buf);		//int�^�ɕύX
			data[y*w+x] = temp;			//1�����Ƃ݂Ȃ��đ���D����ɂ�蕝�w��K�{�D
		}
	}
	return 0;
}

