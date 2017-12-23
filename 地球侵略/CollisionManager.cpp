#include "CollisionManager.h"
#include "SceneManager.h"


CollisionManager::CollisionManager(Player* p) {
	player = p;
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::requestAction(Action act) {
	switch (act) {
	case Action::DmgPlayer:
		damagePlayer();
		break;
	case Action::KillPlayer:
		killPlayer();
		break;

	case Action::GameOver:
		gameOver();
		break;
	case Action::HealPlayer:
		healPlayer();
		break;

	default:
		break;
	}
}

void CollisionManager::damagePlayer() {
	player->modHp(-1);
}

void CollisionManager::killPlayer() {
	player->modHp(-20);
}


void CollisionManager::gameOver() {
	SceneM.ChangeScene(scene::GameOver);
}
void CollisionManager::healPlayer() {
	player->modHp(1);

}