#pragma once
#include "Creature.h"
class DrG :
	public Creature
{
public:
	DrG();
	~DrG();
	DrG(int x, int y, int img, ObjectID id, IObjectManager* Iobj);
	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;

private:
	int img_wait[2];
	int img_damage;
	int img_die[4];
	int hp = 5;
	int counter = 0;

	int spawnTime;
	int invulnerable = 0;
	const int invulnerableTime = 60;
};

