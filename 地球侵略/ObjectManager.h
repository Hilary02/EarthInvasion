#pragma once
#include "DxLib.h"
//#include "Object.h"
#include "HealItem.h"
#include <map>
#include <vector>

class ObjectManager{
public:
	ObjectManager(std::vector<std::vector <int>> vmap);
	~ObjectManager();

	void Loadimg();

	void Update();
	
	std::map<int, int> img;

private:
	Object *objP;
	std::vector<Object> objects;
};


