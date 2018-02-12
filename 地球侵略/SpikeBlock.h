
#pragma once
#include "DxLib.h"
#include "Object.h"

class SpikeBlock :
	public Object {
public:
	SpikeBlock();
	~SpikeBlock();
	SpikeBlock(int x, int y, int img);
	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;
	void collisionCheck(const Collision& target);
private:
	int x;
	int y;
	int imgSpike;
};
