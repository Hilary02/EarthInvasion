#pragma once
#include<fstream>
#include<iostream>//�t�@�C�����o��
#include<string>
#include<sstream> //�����X�g���[��
#include<vector>  //�z��

class IOcsv{
public:
	IOcsv();
	~IOcsv();
	static int ReadMap(char *file, int *data, int w, int h);
	
	static int CSVtoVector(std::string file, std::vector<std::vector<int> >& vec,int w,int h);
};

