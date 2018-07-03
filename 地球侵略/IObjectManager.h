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
	virtual void enemyMoveRangeCalc(int x, int y, int *minX, int *maxX) = 0;
};

