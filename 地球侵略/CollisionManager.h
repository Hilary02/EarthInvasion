#pragma once
#include "ICollisionManager.h"
#include "Player.h"

class CollisionManager :
	public ICollisionManager
{
public:
	CollisionManager(Player* player);
	~CollisionManager();
	void requestAction(ColAction act) override;

private:
	Player* player;
	void damagePlayer();
	void killPlayer();
};

