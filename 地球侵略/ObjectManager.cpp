#include "ObjectManager.h"
#include <memory>
#include <fstream>
#include <iostream>//ファイル入出力
#include <string>
#include <sstream> //文字ストリーム

#include "Item.h"
#include "MoveGround.h"
#include "SpikeBlock.h"
#include "Abyss.h"
#include "Spark.h"
#include "Fire.h"
#include "IObjectManager.h"
#include "Goal.h"
#include "LockedDoor.h"
#include "AntiAlienLaser.h"

ObjectManager::ObjectManager() {
	terrain.clear();
}

ObjectManager::ObjectManager(std::vector<std::vector <int>> vmap, int stage, IStageBase* stageBase) {
	this->player = new Player(vmap, this, stageBase);
	this->vmap = vmap;
	this->stageBase = stageBase;
	stageId = stage;
	Loadimg();
	for (unsigned int i = 0; i < vmap.size(); i++) {
		for (unsigned int j = 0; j < vmap[i].size(); j++) {
			if (4 <= vmap[i][j] && vmap[i][j] <= 9 || 20 <= vmap[i][j] && vmap[i][j] <= 45 || vmap[i][j] == 99) {
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
				case ObjectID::movingFloor:	//動く床
					obje = new MoveGround(x, y, 2, 0.25, 0, true, img[ObjectID::movingFloor]);
					break;
				case ObjectID::difMoveGround:	//逆向きに動く床
					obje = new MoveGround(x, y, 0, 2.25, 0, false, img[ObjectID::movingFloor]);
					break;
				case ObjectID::lockedDoor:
					obje = new LockedDoor(x, y, img[ObjectID::lockedDoor]);
					break;
				case ObjectID::alienLaser:
					obje = new AntiAlienLaser(x, y, img[ObjectID::alienLaser], ObjectID::alienLaser);
					break;
				default:
					obje = new Item(x, y, img[ObjectID::healPot]);	//生成されるべきでない
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
	img[ObjectID::spike] = LoadGraph("data/img/spike.png");
	img[ObjectID::spike_flip] = LoadGraph("data/img/spike_flip.png");
	img[ObjectID::spark] = LoadGraph("data/img/spark.png");
	img[ObjectID::fire] = LoadGraph("data/img/fire.png");
	img[ObjectID::movingFloor] = LoadGraph("data/img/movingFloor.png");
	img[ObjectID::lockedDoor] = LoadGraph("data/img/lockDoor.png");

	img[ObjectID::soldierA] = LoadGraph("data/img/enemy1Wait.png");
	img[ObjectID::soldierB] = LoadGraph("data/img/enemy1Wait.png");
	img[ObjectID::healPot] = LoadGraph("data/img/healPot.png");
	img[ObjectID::goal] = LoadGraph("data/img/clear.png");
	img[ObjectID::alienLaser] = LoadGraph("data/img/LaserA_Wait.png");
	img[ObjectID::robotEnemy] = LoadGraph("data/img/enemy4Wait.png");
}

void ObjectManager::update() {
	player->update();

	int i = 0;
	for (auto &obj : objects) {
		int n = obj->update(*(player->collision));
		if (n == -1) {
			objects.erase(objects.begin() + i);
			i--;
		}
		i++;
	}
	i = 0;
	for (auto &ter : terrain) {
		int n = ter->update(*(player->collision));
		if (n == -1) {
			terrain.erase(terrain.begin() + i);
			i--;
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
	case ObjectID::spike_flip:
		obj = new SpikeBlock(x, y, img[ObjectID::spike_flip], true);
		break;
	case ObjectID::spark:
		obj = new Spark(x, y, img[ObjectID::spark]);
		break;
	case ObjectID::fire:
		obj = new Fire(x, y, img[ObjectID::fire]);
		break;
	case ObjectID::abyss:
		obj = new Abyss(x, y, img[ObjectID::abyss]);
		break;
	case ObjectID::soldierA:
		//Enemyのコンストラクタをオーバーライドしてパラメータを渡せるようにしたい
		obj = new Enemy(x, y, img[ObjectID::soldierA], ObjectID::soldierA, this);
		break;
	case ObjectID::soldierB:
		//Enemyのコンストラクタをオーバーライドしてパラメータを渡せるようにしたい
		obj = new Enemy(x, y, img[ObjectID::soldierB], ObjectID::soldierB, this);
		break;
	case ObjectID::robotEnemy:
		obj = new RobotEnemy(x, y, img[ObjectID::robotEnemy], ObjectID::soldierB, this);
		break;
	case ObjectID::healPot:
		obj = new Item(x, y, img[ObjectID::healPot]);
		break;
	case ObjectID::goal:
		obj = new Goal(x, y, img[ObjectID::goal], stageId, stageBase);
		break;
	case ObjectID::alienLaser:
		obj = new AntiAlienLaser(x, y, img[ObjectID::alienLaser], ObjectID::alienLaser);
		break;
	default:
		obj = new Item(x, y, img[ObjectID::healPot]);	//生成されるべきでない
		break;
	}
	objects.push_back(obj);
}

void ObjectManager::enemyMoveRangeCalc(int x, int y, int *minX, int *maxX)
{
	int indexX = x / 32;
	int indexY = y / 32;
	*maxX = 5 * 32;
	*minX = -5 * 32;
	//ステージの端に敵を配置しないでほしい
	for (int i = 0; i <= 5; i++) {
		if (vmap[indexY][indexX + i] > 0 && vmap[indexY][indexX + i] < 20 ||
			vmap[indexY + 1][indexX + i] > 0 && vmap[indexY + 1][indexX + i] < 20 ||
			vmap[indexY + 2][indexX + i] == 0) {
			//はみ出ないように(i-1)してるはずなんだけどな
			*maxX = (i - 1) * 32;
			break;
		}
	}

	for (int i = 0; i >= -5; i--) {
		if (vmap[indexY][indexX + i] > 0 && vmap[indexY][indexX + i] < 20 ||
			vmap[indexY + 1][indexX + i] > 0 && vmap[indexY + 1][indexX + i] < 20 ||
			vmap[indexY + 2][indexX + i] == 0) {
			*minX = i * 32;
			break;
		}
	}

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
