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

enum class ObjectID {
	none = 0,
	soldierA = 4,	//��ʕ��m
	healPot = 5,	//�񕜃A�C�e��
	spike = 9,		//�Ƃ��Ƃ�
	lockedDoor = 6,	//���Ă����
	moveingFloor = 8,//������
	goal = 99,		//�S�[��

};

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
	//����͖������� getter�͂܂����

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