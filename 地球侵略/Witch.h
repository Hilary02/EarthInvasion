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
	int basePositionY;
	int isPositionY;
	int isUnderTarget;


private:
	int moveHandle[8];
	int atackHandle[8];
	int deadHandle[8];
	int damegeHandle;
	int bulletHandle;
	int targetY;
	bool isFound = false;
	bool isUnder = false;


};

