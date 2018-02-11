#include "ObjectManager.h"
#include <memory>

ObjectManager::ObjectManager() {
	terrain.clear();
}

ObjectManager::ObjectManager(std::vector<std::vector <int>> vmap, int stage) {
	this->player = new Player(vmap,this);
	this->colMgr = new CollisionManager(player);
	stageId = stage;
	Loadimg();
	//IcolMgr = colMgr;
	for (unsigned int i = 0; i < vmap.size(); i++) {
		for (unsigned int j = 0; j < vmap[i].size(); j++) {
			if (vmap[i][j] == 4 || vmap[i][j] == 5 || vmap[i][j] == 9 || vmap[i][j] == 99) {
				Object* obje;
				int y = i * 32;//y座標
				int x = j * 32;//x座標
				int path = 0;    //?I?u?W?F?N?g?ɍ??킹???摜?̃p?X
				path = img[vmap[i][j]];
				switch (vmap[i][j]) {
				case 4:
					obje = new Enemy(x, y, img[10], vmap[i][j], colMgr,this);
					break;
				case 5:
					obje = new Item(x, y, img[20], colMgr);
					break;
				case 9:
					obje = new SpikeBlock(x, y, img[9], colMgr);
					break;
				case 99:	//暫定ゴール
					obje = new  Goal(x, y, img[21], colMgr, stageId);
					break;
				default:
					break;
				}
				objects.push_back(obje);
			}

			if (vmap[i][j] == 6 || vmap[i][j] == 8) {
				Object* obje;
				int y = i * 32;	//y座標
				int x = j * 32;	//x座標
				int path = 0;	//画像ハンドル
				path = img[vmap[i][j]];
				switch (vmap[i][j]) {
				case 6:
					obje = new LockedDoor(x, y, img[6]);
					break;
				case 8:	//動く床
					obje = new MoveGround(x, y, 2, 0.25, 0, img[3]);
					break;
				default:
					break;
				}
				terrain.push_back(obje);	//こちらは地形に保存
			}
		}
	}
	player->setAbsolutePos(300, 600);
}

ObjectManager::~ObjectManager() {
	delete player;
	delete colMgr;

	terrain.clear();
}

void ObjectManager::Loadimg() {
	/* ステージによって読み込む画像も変わるのか？ */
	img[3] = LoadGraph("data/img/moveGround.png");  //3?͓?????
	img[6] = LoadGraph("data/img/lockDoor.png");

	img[9] = LoadGraph("data/img/togetoge.png");	//9togetoge
	img[10] = LoadGraph("data/img/enemy1Wait.png");   //10?͈???
	img[11] = LoadGraph("data/img/");   //11?͒???
	img[12] = LoadGraph("data/img/");   //12?̓x?e??????
	img[13] = LoadGraph("data/img/");   //13?͓Ől??
	img[14] = LoadGraph("data/img/");   //14?͖??@?g??
	img[20] = LoadGraph("data/img/healPot.png");    //20?͉񕜖?
	//img[21] = LoadGraph("data/img/curePod.png"); //21?͓ŏ???

	img[21] = LoadGraph("data/img/clear.png"); //???肠

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
		int n=ter->update(*(player->collision));
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

Player* ObjectManager::getPlayer(){
	return player;
}

std::vector<Object*>& ObjectManager::getObjectList(){
	return objects;
}

std::vector<Object*>& ObjectManager::getTerrainList(){
	return terrain;
}
