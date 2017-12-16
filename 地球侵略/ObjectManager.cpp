#include "ObjectManager.h"
#include<memory>

ObjectManager::ObjectManager()
{
}

//削除予定
ObjectManager::ObjectManager(std::vector<std::vector <int>> vmap, Player * player) {
	Loadimg();
	for (unsigned int i = 0; i < vmap.size(); i++) {
		for (unsigned int j = 0; j < vmap[i].size(); j++) {
			//if (vmap[i][j] == 3 || vmap[i][j] == 4 || vmap[i][j] == 6) {
			if (vmap[i][j] == 4) {

				Object* obje;
				int y = i * 32;//y座標
				int x = j * 32;//x座標
				int path = 0;    //オブジェクトに合わせた画像のパス
				path = img[vmap[i][j]];
				switch (vmap[i][j])
				{

					/*case 3:
						obje = GroundFloor(x, y, img[3]);
						break;
					case 10:
						obje = Enemy(x, y, img[4]);
						break;*/

				case 4:
					//obje = new Enemy(x, y, img[10], vmap[i][j]);
					obje = new Enemy(x, y, img[10], vmap[i][j]);

		/*		case 3:
					obje = GroundFloor(x, y, img[3]);
					break;
				case 10:
					obje = Enemy(x, y, img[10]);
					break;
				case 11:
					obje = Enemy(x, y, img[11]);
					break;
				case 12:
					obje = Enemy(x, y, img[12]);
					break;
				case 13:
					obje = Enemy(x, y, img[13]);
					break;
				case 14:
					obje = Enemy(x, y, img[14]);
					break;
				case 20:
					obje = Item(x, y, img[20]);
					break;
				case 21:
					obje = Item(x, y, img[21]);
					*/
					break;

				default:
					break;
				}
				objects.push_back(obje);
			}
		}
	}
	this->player = player;
}
//
//ObjectManager::ObjectManager(std::vector<std::vector<int>> vmap, Player * player){
//	Loadimg();
//	for (unsigned int i = 0; i < vmap.size(); i++) {
//		for (unsigned int j = 0; j < vmap[i].size(); j++) {
//			if (vmap[i][j] == 3 || vmap[i][j] == 4 || vmap[i][j] == 6) {
//				Object obje;
//				int x = i * 32;//x座標
//				int y = j * 32;//y座標
//				int path = 0;    //オブジェクトに合わせた画像のパス
//				path = img[vmap[i][j]];
//				switch (vmap[i][j])
//				{
//				case 6:
//					obje = HealItem(x, y, img[6]);
//				default:
//					break;
//				}
//				objects.push_back(obje);
//			}
//		}
//	}
//	this->player = player;
//}


ObjectManager::~ObjectManager() {
}

void ObjectManager::Loadimg() {
	img[3] = LoadGraph("data/img/groundFloor.png");  //3は動く床
	img[10] = LoadGraph("data/img/enemy1Wait.png");   //10は一般兵
	img[11] = LoadGraph("data/img/");   //11は中将
	img[12] = LoadGraph("data/img/");   //12はベテラン兵
	img[13] = LoadGraph("data/img/");   //13は毒人間
	img[14] = LoadGraph("data/img/");   //14は魔法使い
	img[20] = LoadGraph("data/img/healPot.png");    //20は回復薬
	img[21] = LoadGraph("data/img/curePod.png"); //21は毒消し
}

void ObjectManager::Update(){
	for (auto &obj : objects) {
		obj->Update(*(player->collision));
	}
}

void ObjectManager::Draw(int drawX, int drawY){
	for (auto obj : objects){
		obj->Draw(drawX, drawY);
	}
}