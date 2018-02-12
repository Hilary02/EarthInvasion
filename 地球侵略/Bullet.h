#pragma once
#include "Object.h"
class Bullet :
	public Object
{
public:
	Bullet();
	Bullet(int, int, int, bool);
	~Bullet();

	int remit = 0;

	bool Update();
	void Draw(int, int);

private:
	bool isR;
};

