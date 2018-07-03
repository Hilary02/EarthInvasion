#pragma once
#include "Object.h"
class AntiAlienLaser :
	public Object
{
public:
	AntiAlienLaser();
	~AntiAlienLaser();
	AntiAlienLaser(int, int, int, ObjectID id);
	int AntiAlienLaser::update(const Collision &pl);
	void Draw(int, int);
	void LoadImg();

private:
	int timer = 0;
	int laserImg[20];
	
};