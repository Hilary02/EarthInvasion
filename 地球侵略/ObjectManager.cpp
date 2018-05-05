#include "ObjectManager.h"
#include <memory>
#include <fstream>
#include <iostream>//ファイル入出力
#include <string>
#include <sstream> //文字ストリーム

#include "Item.h"
#include "MoveGround.h"
#include "SpikeBlock.h"
#include "spark.h"
#include "IObjectManager.h"
#include "Goal.h"
#include "LockedDoor.h"

ObjectManager::ObjectManager() {
	terrain.clear();
}

ObjectManager::ObjectManager(std::vector<std::vector <int>> vmap, int stage) {
	this->player = new Player(vmap, this);
	stageId = stage;
	Loadimg();
	for (unsigned int i = 0; i < vmap.size(); i++) {
		for (unsigned int j = 0; j < vmap[i].size(); j++) {
			if (4 <= vmap[i][j] && vmap[i][j] <= 9 || 20 <= vmap[i][j] && vmap[i][j] <= 39 || vmap[i][j] == 99) {
				int y = i * 32;	//y座標
				int x = j * 32;	//x座標
				addObject(vmap[i][j], x, y);
			}

			if (10 <= vmap[i][j] && vmap[i][j] <= 19) {
				Object* obje;
				int y = i * 32;	//y座標
				int x = j * 32;	//x座標
				int path = 0;	//画像ハンドル
				switch ((ObjectID)vmap[i][j]) {
				case ObjectID::moveingFloor:	//動く床
					obje = new MoveGround(x, y, 2, 0.25, 0, img[ObjectID::moveingFloor]);
					break;
				case ObjectID::lockedDoor:
					obje = new LockedDoor(x, y, img[ObjectID::lockedDoor]);
					break;
				default:
					return;
					break;
				}
				terrain.push_back(obje);	//こちらは地形に保存
			}
		}
	}
}

ObjectManager::~ObjectManager() {
	delete player;
	objects.clear();
	terrain.clear();
}

int ObjectManager::readScenario(std::string file) {
	std::string str;	//行を格納
	std::string buf;	//値を格納
	int temp;
	std::ifstream ifs(file);	//ファイルのオープン
	if (!ifs) return -1;

	while (getline(ifs, str)) {
		std::vector<int> splited;
		std::istringstream stream(str);
		while (getline(stream, buf, ',')) {
			if (buf.size() != 0) {
				temp = std::stoi(buf);		//int型に変更
			}
			else {
				temp = 0;
			}
			splited.push_back(temp);
		}
	}

	ifs.close();
	return 0;
}

void ObjectManager::Loadimg() {
	/* ステージによって読み込む画像も変わるのか？ */
	img[ObjectID::spike] = LoadGraph("data/img/togetoge.png");
	img[ObjectID::spark] = LoadGraph("data/img/spark.png");
	img[ObjectID::moveingFloor] = LoadGraph("data/img/moveGround.png");
	img[ObjectID::lockedDoor] = LoadGraph("data/img/lockDoor.png");

	img[ObjectID::soldierA] = LoadGraph("data/img/enemy1Wait.png");
	img[ObjectID::healPot] = LoadGraph("data/img/healPot.png");
	img[ObjectID::goal] = LoadGraph("data/img/clear.png");
}

void ObjectManager::update() {
	player->update();

	int i = 0;
	for (auto &obj : objects) {
		int n = obj->update(*(player->collision));
		if (n == -1) {
			objects.erase(objects.begin() + i);
		}
		i++;
	}
	i = 0;
	for (auto &ter : terrain) {
		int n = ter->update(*(player->collision));
		if (n == -1) {
			terrain.erase(terrain.begin() + i);
		}
		i++;
	}
}

void ObjectManager::Draw(int drawX, int drawY) {
	player->Draw(drawX, drawY);

	for (auto obj : objects) {
		obj->Draw(drawX, drawY);
	}
	for (auto &ter : terrain) {
		ter->Draw(drawX, drawY);
	}
}

void ObjectManager::addObject(Object* obj) {
	objects.push_back(obj);
}

void ObjectManager::addObject(int id, int x, int y, int hp, int moveUL, int moveRD, int etc1, int etc2) {
	Object* obj;
	switch ((ObjectID)id) {
	case ObjectID::spike:
		obj = new SpikeBlock(x, y, img[ObjectID::spike]);
		break;
	case ObjectID::spark:
		obj = new Spark(x, y, img[ObjectID::spark]);
		break;
	case ObjectID::soldierA:
		//Enemyのコンストラクタをオーバーライドしてパラメータを渡せるようにしたい
		obj = new Enemy(x, y, img[ObjectID::soldierA], ObjectID::soldierA, this);
		break;
	case ObjectID::healPot:
		obj = new Item(x, y, img[ObjectID::healPot]);
		break;
	case ObjectID::goal:
		obj = new Goal(x, y, img[ObjectID::goal], stageId);
		break;
	default:
		return;
		break;
	}
	objects.push_back(obj);
}

std::vector<Object*>& ObjectManager::getObjectList() { return objects; }
std::vector<Object*>& ObjectManager::getTerrainList() { return terrain; }

int ObjectManager::getImageHandle(ObjectID id) {
	if (img.count(id) == 1) {
		return img[id];
	}
	else {
		printfDx("Don't have Handle!");
		return 0;
	}
}
Player* ObjectManager::getPlayer() { return player; }
