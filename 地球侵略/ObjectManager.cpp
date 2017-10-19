#include "ObjectManager.h"

ObjectManager::ObjectManager(std::vector<std::vector <int>> vmap){
	Loadimg();
	for (int i = 0; i < vmap.size(); i++) {
		for (int j = 0; j < vmap[i].size(); j++) {
			if (vmap[i][j] == 3 || vmap[i][j] == 4 || vmap[i][j] == 6) {
				int x = i * 32;//x���W
				int y = j * 32;//y���W
				char* path;    //�I�u�W�F�N�g�ɍ��킹���摜�̃p�X
				Object obje(x , y , path);   //obje(x, y, path); ����������炵��
				objects.push_back(obje);
			}
		}
	}
}


ObjectManager::~ObjectManager(){
}

void ObjectManager::Loadimg(){
	img["enemy"] = LoadGraph("data/img/enemy1Wait.png");
	img["ground"] = LoadGraph("data/img/groundFloor.png");
	img["heal"] = LoadGraph("data/img/healPot.png");

}
