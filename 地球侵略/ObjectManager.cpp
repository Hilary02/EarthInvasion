#include "ObjectManager.h"

ObjectManager::ObjectManager(std::vector<std::vector <int>> vmap) {
	Loadimg();
	for (int i = 0; i < vmap.size(); i++) {
		for (int j = 0; j < vmap[i].size(); j++) {
			if (vmap[i][j] == 3 || vmap[i][j] == 4 || vmap[i][j] == 6) {
				Object obje;
				int x = i * 32;//x���W
				int y = j * 32;//y���W
				int path = 0;    //�I�u�W�F�N�g�ɍ��킹���摜�̃p�X
				path = img[vmap[i][j]];
				switch (vmap[i][j])
				{
				case 6:
					obje = HealItem(x, y, img[6]);
				default:
					break;
				}
				Object obje(x, y, path);   //obje(x, y, path); ����������炵��
				objects.push_back(obje);
			}
		}
	}
}


ObjectManager::~ObjectManager() {
}

void ObjectManager::Loadimg() {
	img[3] = LoadGraph("data/img/enemy1Wait.png");   //3�͓G
	img[4] = LoadGraph("data/img/groundFloor.png");  //4�͓�����
	img[6] = LoadGraph("data/img/healPot.png");    //�U�̓A�C�e��

}

void ObjectManager::Update()
{
	for (auto obj : objects) {
		obj.Update();
	}
}

