#include "ObjectManager.h"
#include <memory>

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
				path = img[vmap[i][j]];
				switch ((ObjectID)vmap[i][j]) {
				case ObjectID::spike:
					obje = new SpikeBlock(x, y, img[9]);
					break;
				case ObjectID::soldierA:
					obje = new Enemy(x, y, img[10], ObjectID::soldierA, this);
					break;
				case ObjectID::healPot:
					obje = new Item(x, y, img[20]);
					break;
				case ObjectID::goal:	//暫定ゴール
					obje = new  Goal(x, y, img[21], stageId);
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
				path = img[vmap[i][j]];
				switch ((ObjectID)vmap[i][j]) {
				case ObjectID::moveingFloor:	//動く床
					obje = new MoveGround(x, y, 2, 0.25, 0, img[3]);
					break;
				case ObjectID::lockedDoor:
					obje = new LockedDoor(x, y, img[6]);
					break;
				default:
					break;
				}
				terrain.push_back(obje);	//こちらは地形に保存
			}
		}
	}
	player->setAbsolutePos(100, 600);
}

ObjectManager::~ObjectManager() {
	delete player;
	objects.clear();
	terrain.clear();
}

void ObjectManager::Loadimg() {
	/* ステージによって読み込む画像も変わるのか？ */
	img[3] = LoadGraph("data/img/moveGround.png");
	img[6] = LoadGraph("data/img/lockDoor.png");

	img[9] = LoadGraph("data/img/togetoge.png");
	img[10] = LoadGraph("data/img/enemy1Wait.png");
	img[11] = LoadGraph("data/img/");
	img[12] = LoadGraph("data/img/");
	img[13] = LoadGraph("data/img/");
	img[14] = LoadGraph("data/img/");
	img[20] = LoadGraph("data/img/healPot.png");
	img[21] = LoadGraph("data/img/clear.png"); //ゴール
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

Player* ObjectManager::getPlayer() {
	return player;
}

void ObjectManager::setObjectList(Object* obj) {
	objects.push_back(obj);

}

std::vector<Object*>& ObjectManager::getObjectList() {
	return objects;
}

std::vector<Object*>& ObjectManager::getTerrainList() {
	return terrain;
}
