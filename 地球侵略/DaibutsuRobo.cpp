#include "DaibutsuRobo.h"

DaibutsuRobo::DaibutsuRobo() {}

DaibutsuRobo::DaibutsuRobo(int x, int y, int img, ObjectID id, IObjectManager * Iobj, int stageID, IStageBase * stage) {
	this->IobjMgr = Iobj;
	this->x = x;
	this->y = y;
	this->imgHandle = img;
	this->id = id;
	setHp(5);
	img_body = LoadGraph("data/img/Daibutsu/Daibutsu_head.png");
	img_head = LoadGraph("data/img/Daibutsu/Daibutsu_head.png");

	//LoadDivGraph("data/img/DrG/enemy5Die.png", 4, 4, 1, 64, 64, img_die);
	collision = new Collision(20, 16, 20, 48);
	state = State::alive;

	this->stageId = stageID;
	this->Istage = stage;

}

DaibutsuRobo::~DaibutsuRobo() {}

int DaibutsuRobo::update(const Collision & playerCol){
	return 0;
}

void DaibutsuRobo::Draw(int drawX, int drawY){
}
