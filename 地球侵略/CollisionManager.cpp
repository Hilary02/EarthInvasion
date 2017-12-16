#include "CollisionManager.h"



CollisionManager::CollisionManager(Player* p){
	player = p;
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::requestAction(ColAction act){
	switch (act) {
	case ColAction::DmgPlayer:
		damagePlayer();
		break;
	case ColAction::KillPlayer:
		killPlayer();
		break;
	default:
		break;
	}
}

void CollisionManager::damagePlayer(){
	player->modHp(-1);
}

void CollisionManager::killPlayer(){
	player->modHp(-20);
}
