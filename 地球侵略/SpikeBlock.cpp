#include "SpikeBlock.h"

SpikeBlock::SpikeBlock() {}
SpikeBlock::~SpikeBlock() {}

SpikeBlock::SpikeBlock(int x, int y, int img, bool flip) {
	this->x = x;
	this->y = y;
	this->imgSpike = img;
	this->id = ObjectID::spike;
	this->flip = flip;

	collision = new Collision(0, -2, 32, 16);
}

int SpikeBlock::update(const Collision & playerCol) {
	collision->updatePos(x, y);
	collisionCheck(playerCol);

	return 0;
}

void SpikeBlock::Draw(int drawX, int drawY) {
	DrawGraph(x - drawX, y - drawY, imgSpike, true);
	DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);
}

void SpikeBlock::collisionCheck(const Collision & target) {
	//プレイヤー側での処理に変更
}
