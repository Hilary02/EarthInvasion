#pragma once
#include "Enemy.h"
class RobotEnemy :
	public Enemy
{
public:
	RobotEnemy(int x, int y, int img, IObjectManager* Iobj);
	~RobotEnemy();
	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
	//void MoveCommon() override;
	//void AtackCommon() override;


};

