#include "ObjectManager.h"

ObjectManager::ObjectManager()
{
}

//削除予定
ObjectManager::ObjectManager(std::vector<std::vector <int>> vmap) {
	Loadimg();
	for (unsigned int i = 0; i < vmap.size(); i++) {
		for (unsigned int j = 0; j < vmap[i].size(); j++) {
			if (vmap[i][j] == 3 || vmap[i][j] == 4 || vmap[i][j] == 6) {
				Object obje;
				int x = i * 32;//x座標
				int y = j * 32;//y座標
				int path = 0;    //オブジェクトに合わせた画像のパス
				path = img[vmap[i][j]];
				switch (vmap[i][j])
				{
				case 6:
					obje = HealItem(x, y, img[6]);
				default:
					break;
				}
				objects.push_back(obje);
			}
		}
	}
}

ObjectManager::ObjectManager(std::vector<std::vector<int>> vmap, Player * player){
	Loadimg();
	for (unsigned int i = 0; i < vmap.size(); i++) {
		for (unsigned int j = 0; j < vmap[i].size(); j++) {
			if (vmap[i][j] == 3 || vmap[i][j] == 4 || vmap[i][j] == 6) {
				Object obje;
				int x = i * 32;//x座標
				int y = j * 32;//y座標
				int path = 0;    //オブジェクトに合わせた画像のパス
				path = img[vmap[i][j]];
				switch (vmap[i][j])
				{
				case 6:
					obje = HealItem(x, y, img[6]);
				default:
					break;
				}
				objects.push_back(obje);
			}
		}
	}
	this->player = player;
}


ObjectManager::~ObjectManager() {
}

void ObjectManager::Loadimg() {
	img[3] = LoadGraph("data/img/enemy1Wait.png");   //3は敵
	img[4] = LoadGraph("data/img/groundFloor.png");  //4は動く床
	img[6] = LoadGraph("data/img/healPot.png");    //６はアイテム

}

void ObjectManager::Update()
{
	for (auto obj : objects) {
		obj.Update();
	}
}

void ObjectManager::Draw(){
	for (auto obj : objects) {
		obj.Draw();
	}
}

void ObjectManager::HitCheck(Object target){
	for (auto obj : objects) {
		obj.hitCheck(target);
	}
}

void ObjectManager::damage_player(){
	player->modHp(-1);
}
