#include "ObjectManager.h"

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

				/*case 3:
					obje = GroundFloor(x, y, img[3]);
					break;*/
				/*case 10:
					obje = Enemy(x, y, img[4]);
					break;*/
				case 20:
					obje = Item(x, y, img[20]);
					break;

				default:
					break;
				}
				objects.push_back(obje);
			}
		}
	}
}


ObjectManager::~ObjectManager() {

}

void ObjectManager::Loadimg() {
	img[3] = LoadGraph("data/img/groundFloor.png");  //3は動く床
	img[10] = LoadGraph("data/img/enemy1Wait.png");   //10は一般兵
	img[11] = LoadGraph("data/img/");   //11はベテラン兵
	img[12] = LoadGraph("data/img/");   //12は大佐
	img[13] = LoadGraph("data/img/");   //13は棒人間
	img[14] = LoadGraph("data/img/");   //14は魔法使い
	img[20] = LoadGraph("data/img/healPot.png");    //20は回復薬
	img[21] = LoadGraph("data/img/curePod.png"); //21は回復薬
	
}

void ObjectManager::Update()
{
	for (auto obj : objects) {
		obj.Update();
	}
}

