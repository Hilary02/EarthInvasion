#pragma once
#include<fstream>
#include<iostream>//ファイル入出力
#include<string>
#include<sstream> //文字ストリーム
#include<vector>  //配列

/**
csvファイルを読み出す処理を行う．
IOcsvは適切でないかも
*/
class IOcsv{
public:
	IOcsv();
	~IOcsv();
	static int ReadMap(char *file, int *data, int w, int h);
	
	static int CSVtoVector(std::string file, std::vector<std::vector<int> >& vec,int w,int h);
};

