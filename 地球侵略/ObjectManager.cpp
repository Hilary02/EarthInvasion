#include "ObjectManager.h"
#include <memory>
#include <fstream>
#include <iostream>//�t�@�C�����o��
#include <string>
#include <sstream> //�����X�g���[��

#include "Item.h"
#include "MoveGround.h"
#include "SpikeBlock.h"
#include "Abyss.h"
#include "Spark.h"
#include "Fire.h"
#include "IObjectManager.h"
#include "Goal.h"
#include "LockedDoor.h"
#include "AntiAlienLaser.h"
#include "DrG.h"
#include "BGMChanger.h"

ObjectManager::ObjectManager() {
	terrain.clear();
}

ObjectManager::ObjectManager(std::vector<std::vector <int>> vmap, int stage, IStageBase* stageBase) {
	this->player = new Player(vmap, this, stageBase);
	this->vmap = vmap;
	this->stageBase = stageBase;
	stageId = stage;
	Loadimg();
	for (unsigned int i = 0; i < vmap.size(); i++) {
		for (unsigned int j = 0; j < vmap[i].size(); j++) {
			if (4 <= vmap[i][j] && vmap[i][j] <= 9 || 20 <= vmap[i][j] && vmap[i][j] <= 45 || 91 <= vmap[i][j] && vmap[i][j] <= 99) {
				int y = i * 32;	//y���W
				int x = j * 32;	//x���W

				addObject(vmap[i][j], x, y);
			}

			if (10 <= vmap[i][j] && vmap[i][j] <= 19) {
				Object* obje;
				int y = i * 32;	//y���W
				int x = j * 32;	//x���W
				int path = 0;	//�摜�n���h��
				switch ((ObjectID)vmap[i][j]) {
				case ObjectID::movingFloor:	//������
					obje = new MoveGround(x, y, 2, 0.25, 0, true, img[ObjectID::movingFloor]);
					break;
				case ObjectID::difMoveGround:	//�t�����ɓ�����
					obje = new MoveGround(x, y, 0, 2.25, 0, false, img[ObjectID::movingFloor]);
					break;
				case ObjectID::lockedDoor:
					obje = new LockedDoor(x, y, img[ObjectID::lockedDoor]);
					break;
				case ObjectID::alienLaser:
					obje = new AntiAlienLaser(x, y, img[ObjectID::alienLaser], ObjectID::alienLaser);
					break;
				default:
					obje = new Item(x, y, img[ObjectID::healPot],ObjectID::healPot);	//���������ׂ��łȂ�
					break;
				}
				terrain.push_back(obje);	//������͒n�`�ɕۑ�
			}
		}
	}
}

ObjectManager::~ObjectManager() {
	delete player;
	objects.clear();
	terrain.clear();
}

int ObjectManager::readScenario(std::string file) {
	std::string str;	//�s���i�[
	std::string buf;	//�l���i�[
	int temp;
	std::ifstream ifs(file);	//�t�@�C���̃I�[�v��
	if (!ifs) return -1;

	while (getline(ifs, str)) {
		std::vector<int> splited;
		std::istringstream stream(str);
		while (getline(stream, buf, ',')) {
			if (buf.size() != 0) {
				temp = std::stoi(buf);		//int�^�ɕύX
			}
			else {
				temp = 0;
			}
			splited.push_back(temp);
		}
	}

	ifs.close();
	return 0;
}

void ObjectManager::Loadimg() {
	/* �X�e�[�W�ɂ���ēǂݍ��މ摜���ς��̂��H */
	img[ObjectID::spike] = LoadGraph("data/img/spike.png");
	img[ObjectID::spike_flip] = LoadGraph("data/img/spike_flip.png");
	img[ObjectID::spark] = LoadGraph("data/img/spark.png");
	img[ObjectID::fire] = LoadGraph("data/img/fire.png");
	img[ObjectID::movingFloor] = LoadGraph("data/img/movingFloor.png");
	img[ObjectID::lockedDoor] = LoadGraph("data/img/lockDoor.png");
	img[ObjectID::soldierA] = LoadGraph("data/img/enemy1Wait.png");
	img[ObjectID::soldierB] = LoadGraph("data/img/enemy1Wait.png");
	img[ObjectID::healPot] = LoadGraph("data/img/healPot.png");
	img[ObjectID::detoxPot] = LoadGraph("data/img/detoxPot.png");
	img[ObjectID::goal] = LoadGraph("data/img/clear.png");
	img[ObjectID::alienLaser] = LoadGraph("data/img/LaserA_Wait.png");
	img[ObjectID::robotEnemy] = LoadGraph("data/img/enemy4Wait.png");
	img[ObjectID::witch] = LoadGraph("data/img/enemy2Wait.png");
}

void ObjectManager::update() {
	player->update();

	std::vector<Object*>::iterator it;
	for (it = objects.begin(); it != objects.end();) {
		int n = (*it)->update(*(player->collision));
		if (n == -1) {
			it = objects.erase(it);
		}
		else {
			it++;
		}
	}
	for (it = terrain.begin(); it != terrain.end();) {
		int n = (*it)->update(*(player->collision));
		if (n == -1) {
			it = terrain.erase(it);
		}
		else {
			it++;
		}
	}
}

void ObjectManager::Draw(int drawX, int drawY) {
	for (auto obj : objects) {
		obj->Draw(drawX, drawY);
	}
	for (auto &ter : terrain) {
		ter->Draw(drawX, drawY);
	}
	player->Draw(drawX, drawY);
}

void ObjectManager::addObject(Object* obj) {
	objects.push_back(obj);
}

void ObjectManager::addObject(int id, int x, int y, int hp, int moveUL, int moveRD, int etc1, int etc2) {
	Object* obj;
	switch ((ObjectID)id) {
	case ObjectID::spike:
		obj = new SpikeBlock(x, y, img[ObjectID::spike]);
		break;
	case ObjectID::spike_flip:
		obj = new SpikeBlock(x, y, img[ObjectID::spike_flip], true);
		break;
	case ObjectID::spark:
		obj = new Spark(x, y, img[ObjectID::spark]);
		break;
	case ObjectID::fire:
		obj = new Fire(x, y, img[ObjectID::fire]);
		break;
	case ObjectID::abyss:
		obj = new Abyss(x, y, img[ObjectID::abyss]);
		break;
	case ObjectID::soldierA:
		//Enemy�̃R���X�g���N�^���I�[�o�[���C�h���ăp�����[�^��n����悤�ɂ�����
		obj = new Enemy(x, y, img[ObjectID::soldierA], ObjectID::soldierA, this);
		break;
	case ObjectID::soldierB:
		//Enemy�̃R���X�g���N�^���I�[�o�[���C�h���ăp�����[�^��n����悤�ɂ�����
		obj = new Enemy(x, y, img[ObjectID::soldierB], ObjectID::soldierB, this);
		break;
	case ObjectID::venomMan:
		obj = new Enemy(x, y, img[ObjectID::soldierA], ObjectID::venomMan, this);
		break;
	case ObjectID::robotEnemy:
		obj = new RobotEnemy(x, y, img[ObjectID::robotEnemy], ObjectID::robotEnemy, this);
		break;
	case ObjectID::witch:	
		obj = new Witch(x,y,img[ObjectID::witch],this);
		break;
	case ObjectID::healPot:
		obj = new Item(x, y, img[ObjectID::healPot],ObjectID::healPot);
		break;
	case ObjectID::detoxPot:
		obj = new Item(x, y, img[ObjectID::detoxPot],ObjectID::detoxPot);
		break;
	case ObjectID::alienLaser:
		obj = new AntiAlienLaser(x, y, img[ObjectID::alienLaser], ObjectID::alienLaser);
		break;
	case ObjectID::DrG:		//�{�X1
		obj = new DrG(x, y, img[ObjectID::DrG], ObjectID::DrG, this, stageId, stageBase);
		break;
	case ObjectID::bgmChanger:
		obj = new BGMChanger(x, y);
		break;

	case ObjectID::goal:
		obj = new Goal(x, y, img[ObjectID::goal], stageId, stageBase);
		break;
	default:
		obj = new Item(x, y, img[ObjectID::healPot], ObjectID::healPot);	//���������ׂ��łȂ�
		break;
	}
	objects.push_back(obj);
}

void ObjectManager::enemyMoveRangeCalc(int x, int y, int *minX, int *maxX)
{
	int indexX = x / 32;
	int indexY = y / 32;
	*maxX = 5 * 32;
	*minX = -5 * 32;
	//�X�e�[�W�̒[�ɓG��z�u���Ȃ��łق���
	for (int i = 0; i <= 5; i++) {
		if (vmap[indexY][indexX + i] > 0 && vmap[indexY][indexX + i] < 20 ||
			vmap[indexY + 1][indexX + i] > 0 && vmap[indexY + 1][indexX + i] < 20 ||
			vmap[indexY + 2][indexX + i] == 0) {
			//�͂ݏo�Ȃ��悤��(i-1)���Ă�͂��Ȃ񂾂��ǂ�
			*maxX = (i - 1) * 32;
			break;
		}
	}

	for (int i = 0; i >= -5; i--) {
		if (vmap[indexY][indexX + i] > 0 && vmap[indexY][indexX + i] < 20 ||
			vmap[indexY + 1][indexX + i] > 0 && vmap[indexY + 1][indexX + i] < 20 ||
			vmap[indexY + 2][indexX + i] == 0) {
			*minX = i * 32;
			break;
		}
	}

}

void ObjectManager::witchMoveRangeCalc(int x, int y, int * minX, int * maxX)
{
	int indexX = x / 32;
	int indexY = y / 32;
	*maxX = 5 * 32;
	*minX = -5 * 32;

	for (int i = 0; i <= 5; i++) {
		if (vmap[indexY][indexX + i] > 0 && vmap[indexY][indexX + i] < 20 ||
			vmap[indexY + 1][indexX + i] > 0 && vmap[indexY + 1][indexX + i] < 20 ) {
			//�͂ݏo�Ȃ��悤��(i-1)���Ă�͂��Ȃ񂾂��ǂ�
			*maxX = (i - 1) * 32;
			break;
		}
	}

	for (int i = 0; i >= -5; i--) {
		if (vmap[indexY][indexX + i] > 0 && vmap[indexY][indexX + i] < 20 ||
			vmap[indexY + 1][indexX + i] > 0 && vmap[indexY + 1][indexX + i] < 20 ) {
			*minX = i * 32;
			break;
		}
	}

}

std::vector<Object*>& ObjectManager::getObjectList() { return objects; }
std::vector<Object*>& ObjectManager::getTerrainList() { return terrain; }

int ObjectManager::getImageHandle(ObjectID id) {
	if (img.count(id) == 1) {
		return img[id];
	}
	else {
		printfDx("Don't have Handle!");
		return 0;
	}
}
Player* ObjectManager::getPlayer() { return player; }
