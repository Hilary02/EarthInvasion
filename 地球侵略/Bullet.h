#pragma once
#include "Object.h"
#define MOVEDIS 2

class Bullet :
	public Object
{
public:
	Bullet();
	//Bullet(int, int, int, bool);
	Bullet(int, int, int, bool, ObjectID id);
	~Bullet();

	int remit = 0;
	int CT = 0;
	int st = 0;

	bool isOutOfRange();
	void Draw(int, int);
	int update(const Collision & playerCol) override;
	bool collisionCheck(const Collision& target);
	void setState(int st);

private:
	bool isR;
	Collision* Bulletcolli;
};

