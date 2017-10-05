#pragma once
#include "DxLib.h"
#include "Object.h"
#include <map>

class ObjectManager{
public:
	ObjectManager();
	~ObjectManager();

	void Loadimg();
	
	std::map<std::string, int> img;

private:
	Object *objP;
};


