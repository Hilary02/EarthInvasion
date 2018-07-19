#include "ObjectManager.h"
#include <memory>
#include <fstream>
#include <iostream>//ƒtƒ@ƒCƒ‹“üo—Í
#include <string>
#include <sstream> //•¶šƒXƒgƒŠ[ƒ€

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

ObjectManager::ObjectManager(std::vector<std::vector <int>> vmap, int stage) {
	this->player = new Player(vmap, this);
	this->vmap = vmap;
	stageId = stage;
	Loadimg();
	for (unsigned int i = 0; i < vmap.size(); i++) {
		for (unsigned int j = 0; j < vmap[i].size(); j++) {
			if (4 <= vmap[i][j] && vmap[i][j] <= 9 || 20 <= vmap[i][j] && vmap[i][j] <= 39 || vmap[i][j] == 99) {
				int y = i * 32;	//yÀ•W
				int x = j * 32;	//xÀ•W

				addObject(vmap[i][j], x, y);
			}

			if (10 <= vmap[i][j] && vmap[i][j] <= 19) {
				Object* obje;
				int y = i * 32;	//yÀ•W
				int x = j * 32;	//xÀ•W
				int path = 0;	//‰æ‘œƒnƒ“ƒhƒ‹
				switch ((ObjectID)vmap[i][j]) {
				case ObjectID::moveingFloor:	//“®‚­°
					obje = new MoveGround(x, y, 2, 0.25, 0, true, img[ObjectID::moveingFloor]);
					break;
				case ObjectID::difMoveGround:	//‹tŒü‚«‚É“®‚­°
					obje = new MoveGround(x, y, 0, 2.25, 0, false, img[ObjectID::moveingFloor]);
					break;
				case ObjectID::lockedDoor:
					obje = new LockedDoor(x, y, img[ObjectID::lockedDoor]);
					break;
				case ObjectID::alienLaser:
					obje = new AntiAlienLaser(x, y, img[ObjectID::alienLaser], ObjectID::alienLaser);
					break;
				default:
					obje = new Item(x, y, img[ObjectID::healPot]);	//¶¬‚³‚ê‚é‚×‚«‚Å‚È‚¢
					break;
				}
				terrain.push_back(obje);	//‚±‚¿‚ç‚Í’nŒ`‚É•Û‘¶
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
	std::string str;	//s‚ğŠi”[
	std::string buf;	//’l‚ğŠi”[
	int temp;
	std::ifstream ifs(file);	//ƒtƒ@ƒCƒ‹‚ÌƒI[ƒvƒ“
	if (!ifs) return -1;

	while (getline(ifs, str)) {
		std::vector<int> splited;
		std::istringstream stream(str);
		while (getline(stream, buf, ',')) {
			if (buf.size() != 0) {
				temp = std::stoi(buf);		//intŒ^‚É•ÏX
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
	/* ƒXƒe[ƒW‚É‚æ‚Á‚Ä“Ç‚İ‚Ş‰æ‘œ‚à•Ï‚í‚é‚Ì‚©H */
	img[ObjectID::spike] = LoadGraph("data/img/togetoge.png");
	img[ObjectID::spark] = LoadGraph("data/img/spark.png");
	img[ObjectID::fire] = LoadGraph("data/img/fire.png");
	img[ObjectID::moveingFloor] = LoadGraph("data/img/moveGround.png");
	img[ObjectID::lockedDoor] = LoadGraph("data/img/lockDoor.png");

	img[ObjectID::soldierA] = LoadGraph("data/img/enemy1Wait.png");
	img[ObjectID::soldierB] = LoadGraph("data/img/enemy1Wait.png");
	img[ObjectID::healPot] = LoadGraph("data/img/healPot.png");
	img[ObjectID::goal] = LoadGraph("data/img/clear.png");
	img[ObjectID::alienLaser] = LoadGraph("data/img/LaserA_Wait.png");
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
		//Enemy‚ÌƒRƒ“ƒXƒgƒ‰ƒNƒ^‚ğƒI[ƒo[ƒ‰ƒCƒh‚µ‚Äƒpƒ‰ƒ[ƒ^‚ğ“n‚¹‚é‚æ‚¤‚É‚µ‚½‚¢
		obj = new Enemy(x, y, img[ObjectID::soldierA], ObjectID::soldierA, this);
		break;
	case ObjectID::soldierB:
		//Enemy‚ÌƒRƒ“ƒXƒgƒ‰ƒNƒ^‚ğƒI[ƒo[ƒ‰ƒCƒh‚µ‚Äƒpƒ‰ƒ[ƒ^‚ğ“n‚¹‚é‚æ‚¤‚É‚µ‚½‚¢
		obj = new Enemy(x, y, img[ObjectID::soldierB], ObjectID::soldierB, this);
		break;
	case ObjectID::healPot:
		obj = new Item(x, y, img[ObjectID::healPot]);
		break;
	case ObjectID::goal:
		obj = new Goal(x, y, img[ObjectID::goal], stageId);
		break;
	case ObjectID::alienLaser:
		obj = new AntiAlienLaser(x, y, img[ObjectID::alienLaser], ObjectID::alienLaser);
		break;
	default:
		obj = new Item(x, y, img[ObjectID::healPot]);	//¶¬‚³‚ê‚é‚×‚«‚Å‚È‚¢
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
	//ç¾åœ¨ã¯ã‚¨ãƒãƒŸãƒ¼ã®åˆæœŸä½ç½®ãŒxãŒï¼•ä»¥ä¸‹ãªã©ã®é™ç•Œå€¤ä»˜è¿‘ãªã‚‰ãŸã¶ã‚“ã‚¨ãƒ©ãƒ¼ãŒç™ºç”Ÿ
	for (int i = 0; i <= 5; i++) {
		if (vmap[indexY][indexX + i] > 0 && vmap[indexY][indexX + i] < 20 ||
			vmap[indexY + 1][indexX + i] > 0 && vmap[indexY + 1][indexX + i] < 20 ||
			vmap[indexY + 2][indexX + i] == 0) {
			//ãã®ã¾ã¾iã®å€¤ã§è¨ˆç®—ã™ã‚‹ã¨å£ãªã©ã«åŸ‹ã¾ã£ã¦ã—ã¾ã†ãŸã‚(i-1),(i+1)
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
