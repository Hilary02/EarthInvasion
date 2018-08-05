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
	virtual	void collisionCheck(const Collision& target);
	virtual void MoveCommon();
	virtual void AtackCommon();
	virtual void DeadCheck();
	virtual bool IsRangeCheck();
private:
	bool rightFlg = false; //1ŽžŠi”[‚Ì‚½‚ß 
};

