#pragma once
#include "Object.h"
#include <map>
class Item :
	public Object
{
public:
	Item();
	~Item();
	Item(int x, int y, std::map<int, int> imag);
};
