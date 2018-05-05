#include "ObjectManager.h"
#include <memory>
#include <fstream>
#include <iostream>//ファイル入出力
#include <string>
#include <sstream> //文字ストリーム

ObjectManager::ObjectManager() {
	terrain.clear();
}

ObjectManager::ObjectManager(std::vector<std::vector <int>> vmap, int stage) {
	this->player = new Player(vmap, this);
	stageId = stage;
	Loadimg();
	for (unsigned int i = 0; i < vmap.size(); i++) {
		for (unsigned int j = 0; j < vmap[i].size(); j++) {
			//ここを書き換えないと追加できないのはよくないと思う
			if (vmap[i][j] == 4 || vmap[i][j] == (int)ObjectID::soldierA || vmap[i][j] == (int)ObjectID::healPot || vmap[i][j] == 99) {
				Object* obje;
				int y = i * 32;	//y座標
				int x = j * 32;	//x座標
				int path = 0;	//画像ハンドル
				//path = img[vmap[i][j]];
				switch ((ObjectID)vmap[i][j]) {
				case ObjectID::spike:
					obje = new SpikeBlock(x, y, img[ObjectID::spike]);
					break;
				case ObjectID::soldierA:
					obje = new Enemy(x, y, img[ObjectID::soldierA], ObjectID::soldierA, this);
					break;
				case ObjectID::healPot:
					obje = new Item(x, y, img[ObjectID::healPot]);
					break;
				case ObjectID::goal:	//暫定ゴール
					obje = new  Goal(x, y, img[ObjectID::goal], stageId);
					break;
				default:
					break;
				}
				objects.push_back(obje);
			}

			if (10 <= vmap[i][j] && vmap[i][j] <= 19) {
				Object* obje;
				int y = i * 32;	//y座標
				int x = j * 32;	//x座標
				int path = 0;	//画像ハンドル
				//path = img[vmap[i][j]];
				switch ((ObjectID)vmap[i][j]) {
				case ObjectID::moveingFloor:	//動く床
					obje = new MoveGround(x, y, 2, 0.25, 0, img[ObjectID::moveingFloor]);
					break;
				case ObjectID::lockedDoor:
					obje = new LockedDoor(x, y, img[ObjectID::lockedDoor]);
					break;
				default:
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

}

std::vector<Object*>& ObjectManager::getObjectList() { return objects; }
std::vector<Object*>& ObjectManager::getTerrainList() { return terrain; }
int ObjectManager::getImageHandle(ObjectID id){

	return 0;
}
Player* ObjectManager::getPlayer() { return player; }
