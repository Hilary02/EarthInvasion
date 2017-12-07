#pragma once
#include "DxLib.h"
#include "Object.h"
#include "Player.h"
#include "HealItem.h"
#include <map>
#include <vector>

class ObjectManager{
public:
	ObjectManager();
	ObjectManager(std::vector<std::vector <int>> vmap);
	ObjectManager(std::vector<std::vector <int>> vmap,Player* player);
	~ObjectManager();

	void Loadimg();

	void Update();
	void Draw();
	void HitCheck(Object target);
	
	std::map<int, int> img;

private:
	Object *objP;
	std::vector<Object> objects;
	Player *player;

	void damage_player();
};


