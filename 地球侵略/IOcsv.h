#pragma once
#include<fstream>
#include<iostream>//�t�@�C�����o��
#include<string>
#include<sstream> //�����X�g���[��
#include<vector>  //�z��

class IOcsv
{
public:
	IOcsv();
	~IOcsv();
	//static int Readcsv(std::string file, std::vector<std::vector <int>> *data,int w,int h);
	static int Readcsv(std::string file, int *data, int w, int h);
};

