#include "ObjectManager.h"

ObjectManager::ObjectManager(std::vector<std::vector <int>> vmap) {
	Loadimg();
	for (unsigned int i = 0; i < vmap.size(); i++) {
		for (unsigned int j = 0; j < vmap[i].size(); j++) {
			if (vmap[i][j] == 3 || vmap[i][j] == 4 || vmap[i][j] == 6) {
				Object obje;
				int x = i * 32;//x���W
				int y = j * 32;//y���W
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
				case 20:
					obje = HealItem(x, y, img[20]);
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
	img[3] = LoadGraph("data/img/groundFloor.png");  //3�͓�����
	img[10] = LoadGraph("data/img/enemy1Wait.png");   //10�͈�ʕ�
	img[11] = LoadGraph("data/img/");   //11�̓x�e������
	img[12] = LoadGraph("data/img/");   //12�͑卲
	img[13] = LoadGraph("data/img/");   //13�͖_�l��
	img[14] = LoadGraph("data/img/");   //14�͖��@�g��
	img[20] = LoadGraph("data/img/healPot.png");    //20�͉񕜖�
	img[21] = LoadGraph("data/img/curePod.png"); //21�͉񕜖�
	
}

void ObjectManager::Update()
{
	for (auto obj : objects) {
		obj.Update();
	}
}

