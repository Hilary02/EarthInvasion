#include "IOcsv.h"



IOcsv::IOcsv()
{
}


IOcsv::~IOcsv()
{
}


//int IOcsv::Readcsv(std::string file, std::vector<std::vector <int>> *data, int w, int h)
//{
//	//std::ifstream ifs(file.c_str());
//	std::ifstream ifs("map02.csv");
//
//	if (!ifs) {
//		return 1;
//	}
//
//	std::string str;
//	std::string buf;	//�ꎞ�i�[
//	std::vector<int> vi;
//	int temp;
//	//1�s�̂����A������ƃR���}�𕪊�����
//	for (int y = 0; y < h; y++) {
//		//csv�t�@�C����1�s���ǂݍ���
//		getline(ifs, str);
//		std::istringstream stream(str);
//		for (int x = 0; x < w; x++) {
//			getline(stream, buf, ',');
//			temp = std::stoi(buf);
//			vi[x] = temp;
//		}
//		//data[y] = vi;
//		data[y].push_back(vi);
//	}
//	return 0;
//}
//



int IOcsv::Readcsv(std::string file, int *data, int w, int h)
{
	//std::ifstream ifs(file.c_str());
	std::ifstream ifs("data/map/�`���[�g���A���}�b�v.csv");

	if (!ifs) {
		return 1;
	}

	std::string str;
	std::string buf;	//�ꎞ�i�[
	std::vector<int> vi;
	int temp;
	//1�s�̂����A������ƃR���}�𕪊�����
	for (int y = 0; y < h; y++) {
		//csv�t�@�C����1�s���ǂݍ���
		getline(ifs, str);
		std::istringstream stream(str);
		for (int x = 0; x < w; x++) {
			getline(stream, buf, ',');
			temp = std::stoi(buf);
			//1�����ɖ�����菑�������D����ɂ�蕝�w��K�{�D
			data[y*w+x] = temp;
			//DrawFormatString(320 + 32 * x, 16 + 32 * y, GetColor(0, 255, 0), "%d", temp);
		}
	}
	return 0;
}

