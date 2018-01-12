#pragma once
#include "DxLib.h"
#include "Object.h"
#include "Player.h"
#include "Item.h"
#include "Enemy.h"
#include "MoveGround.h"
#include "SpikeBlock.h"
#include <map>
#include <vector>

class ObjectManager{
public:
	ObjectManager();
	//ObjectManager(std::vector<std::vector <int>> vmap);
	ObjectManager(std::vector<std::vector <int>> vmap,Player* player, ICollisionManager* colMgr);
	~ObjectManager();

	void Loadimg();

	void update();
	void Draw(int drawX, int drawY);
	
	std::map<int, int> img;
	static std::vector<Object*> terrain;	//����͖������� getter�͂܂����

private:
	Object *objP;
	std::vector<Object*> objects;

	Player *player;
	ICollisionManager* IcolMgr;
	
};


