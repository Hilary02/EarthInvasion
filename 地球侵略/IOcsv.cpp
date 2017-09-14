#include "IOcsv.h"

IOcsv::IOcsv()
{
}


IOcsv::~IOcsv()
{
}

//csv�t�@�C���̓��e���}�b�v�z��(vector)�ɓǂݍ��ޏ���
//���w���vector�̗v�f����ǂݎ���΂����̂ŕs�v�ɂȂ邩��
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

			try {
				temp = std::stoi(buf);		//int�^�ɕύX
			}
			catch (std::invalid_argument e) {
				temp = 0;
			}
			catch (std::out_of_range e) {
				temp = 0;
			}
			
			vec[y][x] = temp;			//vector���A�N�Z�X���@�͔z��Ɠ��l�ɍs����
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

