#include "IOcsv.h"

IOcsv::IOcsv()
{
}


IOcsv::~IOcsv()
{
}


int IOcsv::CSVtoVector(std::string file, std::vector<std::vector<int> >& vec, int w, int h)
{
	std::string str;	//行を格納
	std::string buf;	//値を一時格納
	int temp;
	//ファイルのオープン
	std::ifstream ifs(file);
	if (!ifs) return 1;

	for (int y = 0; y < h; y++) {
		getline(ifs, str);				//csvファイルを1行読み込む
		std::istringstream stream(str);
		for (int x = 0; x < w; x++) {
			getline(stream, buf, ',');	//カンマで区切る
			temp = std::stoi(buf);		//int型に変更
			vec[y][x] = temp;
		}
	}
	return 0;
}




int IOcsv::ReadMap(char *file, int *data, int w, int h){
	std::string str;	//行を格納
	std::string buf;	//値を一時格納
	int temp;
	//ファイルのオープン
	std::ifstream ifs(file);
	if (!ifs) return 1;


	for (int y = 0; y < h; y++) {		
		getline(ifs, str);				//csvファイルを1行読み込む
		std::istringstream stream(str);
		for (int x = 0; x < w; x++) {
			getline(stream, buf, ',');	//カンマで区切る
			temp = std::stoi(buf);		//int型に変更
			data[y*w+x] = temp;			//1次元とみなして代入．これにより幅指定必須．
		}
	}
	return 0;
}

