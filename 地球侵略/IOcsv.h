#pragma once
#include<fstream>
#include<iostream>//ファイル入出力
#include<string>
#include<sstream> //文字ストリーム
#include<vector>  //配列

class IOcsv
{
public:
	IOcsv();
	~IOcsv();
	//static int Readcsv(std::string file, std::vector<std::vector <int>> *data,int w,int h);
	static int Readcsv(std::string file, int *data, int w, int h);
};

