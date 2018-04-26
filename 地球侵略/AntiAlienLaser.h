#pragma once
#include "Object.h"
class AntiAlienLaser :
	public Object
{
public:
	AntiAlienLaser();
	~AntiAlienLaser();
	AntiAlienLaser(int, int, int, ObjectID id);
	void AntiAlienLaser::update(const Collision);
	void AntiAlienLaser::Draw(int, int);

private:
	int timer = 0;
	int laserImg[20];
	void loadImg();
};