#pragma once
#include <map>
#include <vector>
#include "DxLib.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "Item.h"
#include "MoveGround.h"
#include "SpikeBlock.h"
#include "IObjectManager.h"
#include "Goal.h"
#include "LockedDoor.h"



class ObjectManager :
	private IObjectManager {
public:
	ObjectManager();
	ObjectManager(std::vector<std::vector <int>> vmap, int stage);
	~ObjectManager();

	void Loadimg();

	void update();
	void Draw(int drawX, int drawY);

	std::map<int, int> img;
	//‚±‚ê‚Í–³’ƒ‚©‚È getter‚Í‚Ü‚½Œã‚Å

	Player* getPlayer();

	void setObjectList(Object* obj) override;

	std::vector<Object*>& getObjectList() override;
	std::vector<Object*>& getTerrainList()override;


private:
	int stageId;
	Player *player;
	std::vector<Object*> objects;
	std::vector<Object*> terrain;
};