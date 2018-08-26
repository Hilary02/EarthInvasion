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
	void surfacung();
	void risingOrDescent();
	int update(const Collision & playerCol) override;

	boolean isRight;

private:
	int moveHandle[8];
	int atackHandle[8];
	int deadHandle[8];
	int damegeHandle;
	int bulletHandle;
	bool isUnder;
};

