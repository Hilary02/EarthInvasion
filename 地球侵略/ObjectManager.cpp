#include "ObjectManager.h"
#include<memory>

ObjectManager::ObjectManager()
{
}

//�폜�\��
ObjectManager::ObjectManager(std::vector<std::vector <int>> vmap, Player * player, ICollisionManager* colMgr) {
	Loadimg();
	IcolMgr = colMgr;
	for (unsigned int i = 0; i < vmap.size(); i++) {
		for (unsigned int j = 0; j < vmap[i].size(); j++) {
			//if (vmap[i][j] == 3 || vmap[i][j] == 4 || vmap[i][j] == 6) {
			if (vmap[i][j] == 4) {

				Object* obje;
				int y = i * 32;//y���W
				int x = j * 32;//x���W
				int path = 0;    //�I�u�W�F�N�g�ɍ��킹���摜�̃p�X
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
//				int x = i * 32;//x���W
//				int y = j * 32;//y���W
//				int path = 0;    //�I�u�W�F�N�g�ɍ��킹���摜�̃p�X
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
	img[3] = LoadGraph("data/img/groundFloor.png");  //3�͓�����
	img[10] = LoadGraph("data/img/enemy1Wait.png");   //10�͈�ʕ�
	img[11] = LoadGraph("data/img/");   //11�͒���
	img[12] = LoadGraph("data/img/");   //12�̓x�e������
	img[13] = LoadGraph("data/img/");   //13�͓Ől��
	img[14] = LoadGraph("data/img/");   //14�͖��@�g��
	img[20] = LoadGraph("data/img/healPot.png");    //20�͉񕜖�
	img[21] = LoadGraph("data/img/curePod.png"); //21�͓ŏ���
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