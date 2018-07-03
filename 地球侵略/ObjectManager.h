#pragma once
#include <map>
#include <vector>
#include "DxLib.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"

class ObjectManager :
	private IObjectManager {
public:
	ObjectManager();
	ObjectManager(std::vector<std::vector <int>> vmap, int stage);
	~ObjectManager();

	int readScenario(std::string file);
	void Loadimg();

	void update();
	void Draw(int drawX, int drawY);

	//�쐬�ς�Object�̒��ڒǉ�
	void addObject(Object* obj) override;
	//Object�p�����[�^�w��Œǉ�
	void addObject(int id, int x, int y, int hp = -1, int moveUL = -1, int moveRD = -1, int etc1 = -1, int etc2 = -1);
	//敵兵の動く範囲計算
	void enemyMoveRangeCalc(int x, int y, int *minX, int *maxX);

	std::vector<Object*>& getObjectList() override;
	std::vector<Object*>& getTerrainList() override;
	int getImageHandle(ObjectID id) override;
	Player* getPlayer();
	std::vector<std::vector <int>> vmap;


private:
	int stageId;
	Player *player;
	std::vector<Object*> objects;
	std::vector<Object*> terrain;
	std::map<ObjectID, int> img;
};