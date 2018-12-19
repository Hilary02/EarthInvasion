#pragma once
#include <map>
#include <vector>
#include "DxLib.h"
#include "Object.h"
#include "Player.h"
#include "Enemy.h"
#include "RobotEnemy.h"
#include "Witch.h"
#include "IStageBase.h"

class ObjectManager :
	private IObjectManager {
public:
	ObjectManager();
	ObjectManager(std::vector<std::vector <int>> vmap, int stage,IStageBase* stageBase);
	~ObjectManager();

	int readScenario(std::string file);
	void Loadimg();

	void update();
	void Draw(int drawX, int drawY);

	//作成済みObjectの直接追加
	void addObject(Object* obj) override;
	//Objectパラメータ指定で追加
	void addObject(int id, int x, int y, int hp = -1, int moveUL = -1, int moveRD = -1, int etc1 = -1, int etc2 = -1);
	//エネミーの移動範囲設定する
	void enemyMoveRangeCalc(int x, int y, int *minX, int *maxX);
	//魔女の移動範囲を設定する
	void witchMoveRangeCalc(int x, int y, int *minX, int *maxX);

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
	IStageBase* stageBase;
};