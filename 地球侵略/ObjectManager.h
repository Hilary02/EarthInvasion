#pragma once
#include "DxLib.h"
#include "Object.h"
#include "Player.h"
#include "HealItem.h"
#include "Enemy.h"
#include <map>
#include <vector>
#include "iHitAction.h"


class ObjectManager:public iHitAction{
public:
	ObjectManager();
	//ObjectManager(std::vector<std::vector <int>> vmap);
	ObjectManager(std::vector<std::vector <int>> vmap,Player* player);
	~ObjectManager();

	void Loadimg();

	void Update();
	void Draw(int drawX, int drawY);
	void HitCheck(Object* target);

	//�����蔻��̏��������s
	int doHitAction(int id) override;
	
	std::map<int, int> img;

private:
	Object *objP;
	std::vector<Object*> objects;

	Player *player;

	void damage_player();

};


