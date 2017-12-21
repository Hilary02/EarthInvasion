#pragma once
#include "Object.h"
class Bullet :
	public Object
{
public:
	Bullet();
	Bullet(int, int, int, bool, ICollisionManager*);
	~Bullet();

	int remit;

	void Update();
	void Draw(int, int);

private:
	bool isR;
};

