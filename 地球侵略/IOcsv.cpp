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
//	std::string buf;	//一時格納
//	std::vector<int> vi;
//	int temp;
//	//1行のうち、文字列とコンマを分割する
//	for (int y = 0; y < h; y++) {
//		//csvファイルを1行ずつ読み込む
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
	std::ifstream ifs("data/map/チュートリアルマップ.csv");

	if (!ifs) {
		return 1;
	}

	std::string str;
	std::string buf;	//一時格納
	std::vector<int> vi;
	int temp;
	//1行のうち、文字列とコンマを分割する
	for (int y = 0; y < h; y++) {
		//csvファイルを1行ずつ読み込む
		getline(ifs, str);
		std::istringstream stream(str);
		for (int x = 0; x < w; x++) {
			getline(stream, buf, ',');
			temp = std::stoi(buf);
			//1次元に無理やり書き換え．これにより幅指定必須．
			data[y*w+x] = temp;
			//DrawFormatString(320 + 32 * x, 16 + 32 * y, GetColor(0, 255, 0), "%d", temp);
		}
	}
	return 0;
}

