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

	bool Update();
	void Draw(int, int);
	int update(const Collision & playerCol) override;
	bool collisionCheck(const Collision& target);

private:
	bool isR;
	Collision* Bulletcolli;
};

