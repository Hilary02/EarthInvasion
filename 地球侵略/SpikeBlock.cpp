#include "SpikeBlock.h"



SpikeBlock::SpikeBlock()
{
}


SpikeBlock::~SpikeBlock()
{
}
SpikeBlock::SpikeBlock(int x, int y, int img, ICollisionManager* IcolMgr) {
	this->x = x;	
	this->y = y;
	this->imgSpike = img;
	collision = new Collision(0-2, 0-2, 256, 64);
	this->IcolMgr = IcolMgr;

}

void SpikeBlock::Update(const Collision & playerCol)
{
	collision->updatePos(x, y);
	collisionCheck(playerCol);
}

void SpikeBlock::Draw(int drawX, int drawY)
{
		DrawGraph(x - drawX, y - drawY, imgSpike, true);
}

void SpikeBlock::collisionCheck(const Collision & target) {
	int isCol = collision->doCollisonCheck((target.hitRange));
	if (isCol) {
		IcolMgr->requestAction(Action::DmgPlayer);
	}
}
