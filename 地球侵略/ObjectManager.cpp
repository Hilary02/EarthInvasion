#include "ObjectManager.h"
#include "Item.h"
#include<memory>

#include "Goal.h"

ObjectManager::ObjectManager()
{
}

//?폜?\??
ObjectManager::ObjectManager(std::vector<std::vector <int>> vmap, Player * player, ICollisionManager* colMgr) {
	Loadimg();
	IcolMgr = colMgr;
	for (unsigned int i = 0; i < vmap.size(); i++) {
		for (unsigned int j = 0; j < vmap[i].size(); j++) {
			//if (vmap[i][j] == 3 || vmap[i][j] == 4 || vmap[i][j] == 6) {


			if (vmap[i][j] ==  4 || vmap[i][j] == 5|| vmap[i][j] == 8 || vmap[i][j] == 9|| vmap[i][j] == 99) {



				Object* obje;
				int y = i * 32;//y???W
				int x = j * 32;//x???W
				int path = 0;    //?I?u?W?F?N?g?ɍ??킹???摜?̃p?X
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
					obje = new Enemy(x, y, img[10], vmap[i][j],IcolMgr);
					break;
<<<<<<< HEAD

=======
				case 5:
					obje = new Item(x, y, img[20],IcolMgr);
					break;
>>>>>>> origin/healItem
		/*		case 3:
					obje = GroundFloor(x, y, img[3]);

					break;
					*/
				case 8:
					obje = new MoveGround(x, y, 2, 0.25, 0, img[3]);
					break;
				case 9:
					obje = new SpikeBlock(x, y, img[9], IcolMgr);
					break;
/*
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


				case 99:
					obje =new  Goal(x, y, img[21], IcolMgr);
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
//				int x = i * 32;//x???W
//				int y = j * 32;//y???W
//				int path = 0;    //?I?u?W?F?N?g?ɍ??킹???摜?̃p?X
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
	img[3] = LoadGraph("data/img/moveGround.png");  //3?͓?????
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

void ObjectManager::update(){
	//DrawFormatString(90,90,0x000000,0xFFFFFF)
	int i = 0;
	for (auto &obj : objects) {
		i++;
		int n=obj->update(*(player->collision));
		if (n == -1) {
			objects.erase(objects.begin() +i-1);
		}
	}
}

void ObjectManager::Draw(int drawX, int drawY){
	for (auto obj : objects){
		obj->Draw(drawX, drawY);
	}
}
