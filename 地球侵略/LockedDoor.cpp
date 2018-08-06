#include "LockedDoor.h"
#include "SoundManager.h"

LockedDoor::LockedDoor() {}

LockedDoor::~LockedDoor() {}

LockedDoor::LockedDoor(int x, int y, int img) {
	this->x = x;
	this->y = y;
	moveTo = y - 96;
	this->img = img;
	collision = new Collision(0, 0, 16, 96);
	id = ObjectID::lockedDoor;
}

int LockedDoor::update(const Collision & playerCol) {
	collision->updatePos(x, y);
	//プレイヤーが兵士状態なら自分を消す
	int isCol = collision->doCollisonCheck(playerCol.hitRange);
	if (isCol == 1 && playerCol.playerParasite != 0) {
		open = true;
	}
	if (open) openAnimation();
	if (remove) return -1;
	return 0;
}

void LockedDoor::Draw(int drawX, int drawY) {
	DrawGraph(x - drawX, y - drawY, img, true);

	//当たり判定領域の表示
	//DrawBox(collision->hitRange.xPos + collision->hitRange.xOffset - drawX, collision->hitRange.yPos + collision->hitRange.yOffset - drawY, collision->hitRange.xPos + collision->hitRange.xOffset + collision->hitRange.xSize - drawX, collision->hitRange.yPos + collision->hitRange.yOffset + collision->hitRange.ySize - drawY, 0xFF00FF, false);
}

void LockedDoor::openAnimation() {
	if (y >= moveTo) { y--; }
	if (y <= moveTo) {
		SoundM.Se("data/se/door.wav");
		remove = true;
	}
}
