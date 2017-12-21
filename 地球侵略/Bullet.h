#pragma once
#include "Object.h"
class Bullet :
	public Object
{
public:
	Bullet();
	~Bullet();

private:
	int x;
	int y;
};

