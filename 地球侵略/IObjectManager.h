#pragma once
#include <vector>
#include "Object.h"

class IObjectManager {
public:
	virtual void setObjectList(Object* obj) = 0;
	virtual std::vector<Object*>& getObjectList() = 0;
	virtual std::vector<Object*>& getTerrainList() = 0;
};

