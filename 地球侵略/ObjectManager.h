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

	//ì¬Ï‚İObject‚Ì’¼Ú’Ç‰Á
	void addObject(Object* obj) override;
	//Objectƒpƒ‰ƒ[ƒ^w’è‚Å’Ç‰Á
	void addObject(int id, int x, int y, int hp = -1, int moveUL = -1, int moveRD = -1, int etc1 = -1, int etc2 = -1);
	//æ•µå…µã®å‹•ãç¯„å›²è¨ˆç®—
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