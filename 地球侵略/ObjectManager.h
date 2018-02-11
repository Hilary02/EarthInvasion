#pragma once
#include "DxLib.h"
#include "Object.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "MoveGround.h"
#include "SpikeBlock.h"
#include "IObjectManager.h"
#include "CollisionManager.h"
#include <map>
#include <vector>

class ObjectManager:
private IObjectManager {
public:
	ObjectManager();
	//ObjectManager(std::vector<std::vector <int>> vmap);
	ObjectManager(std::vector<std::vector <int>> vmap,int stage);
	~ObjectManager();

	void Loadimg();

	void update();
	void Draw(int drawX, int drawY);
	
	std::map<int, int> img;
	//����͖������� getter�͂܂����

	Player* getPlayer();
	std::vector<Object*>& getObjectList() override;
	std::vector<Object*>& getTerrainList()override;


private:
	Object *objP;
	std::vector<Object*> objects;
	std::vector<Object*> terrain;

	Player *player;
	//ICollisionManager* IcolMgr;
	CollisionManager* colMgr;
	int stageId;
	
};


