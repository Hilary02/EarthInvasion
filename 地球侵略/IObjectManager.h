#pragma once
#include <vector>
//#include "Object.h"
class Object;

class IObjectManager {
public:
	virtual void addObject(Object* obj) = 0;
	virtual std::vector<Object*>& getObjectList() = 0;
	virtual std::vector<Object*>& getTerrainList() = 0;
	virtual int getImageHandle(ObjectID id) = 0;
};

