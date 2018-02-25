#pragma once
#include "Object.h"
class Bullet :
	public Object
{
public:
	Bullet();
	Bullet(int, int, int, bool);
	Bullet(int, int, int, bool, int id);
	~Bullet();

	int remit = 0;
	int CT = 0;
	int st = 0;

	bool Update();
	void Draw(int, int);
	int update(const Collision & playerCol) override;
	bool collisionCheck(const Collision& target);
	void setState(int st);

private:
	bool isR;
	Collision* Bulletcolli;
};

