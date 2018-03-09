#include "SpikeBlock.h"

SpikeBlock::SpikeBlock() {}
SpikeBlock::~SpikeBlock() {}

SpikeBlock::SpikeBlock(int x, int y, int img) {
	this->x = x;
	this->y = y;
	this->imgSpike = img;
	this->id = ObjectID::spike;
	collision = new Collision(0 - 2, 0 - 2, 256, 64);
}

int SpikeBlock::update(const Collision & playerCol)
{
	collision->updatePos(x, y);
	collisionCheck(playerCol);

	return 0;
}

void SpikeBlock::Draw(int drawX, int drawY)
{
	DrawGraph(x - drawX, y - drawY, imgSpike, true);
}

void SpikeBlock::collisionCheck(const Collision & target) {
	//プレイヤー側での処理に変更
}
