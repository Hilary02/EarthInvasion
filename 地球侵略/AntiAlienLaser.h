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
	void AntiAlienLaser::Draw(int, int);

private:
	int timer = 0;
	int laserImg[20];
	void loadImg();
};