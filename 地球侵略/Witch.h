#pragma once
#include "Enemy.h"
class Witch :
	public Enemy
{
public:
	Witch(int x, int y, int img, IObjectManager* Iobj);
	~Witch();
	void Draw(int drawX, int drawY) override;
	void attack();
	void floating();
	void risingOrDescent();
	void collsionCheck(const Collision & target);
	int update(const Collision & playerCol) override;

private:
	int moveHandle[8];
	int atackHandle[8];
	int deadHandle[8];
	int damegeHandle;
	int bulletHandle;
	int targetY;
	int targetX;
	int basePositionY;

	bool isPositionY;
	bool isUnderTarget;
	bool isFound = false;
	bool isUnder = false;


};

