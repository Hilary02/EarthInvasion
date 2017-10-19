#pragma once
#include "DxLib.h"
#include "Object.h"
#include <map>
#include <vector>

class ObjectManager{
public:
	ObjectManager(std::vector<std::vector <int>> vmap);
	~ObjectManager();

	void Loadimg();

	
	std::map<std::string, int> img;

private:
	Object *objP;
	std::vector<Object> objects;
};


