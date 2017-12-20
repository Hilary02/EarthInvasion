#include "MovingFloor.h"



MovingFloor::MovingFloor(){
}


MovingFloor::~MovingFloor()
{
}

void MovingFloor::Update(const Collision & playerCol){
	Frame++;
	if (Frame % 3 == 0) {
		y += moveSpeed;
		if (moveMax <= y) moveSpeed = -1;
		if (moveMin >= y)moveSpeed = 1;

	}
}

void MovingFloor::Draw(int drawX, int drawY){
	//DrawGraph(x-drawX,y-drawY,)
	DrawBox(x - drawX, y - drawY,64,64, 0x00FFFF, true);
}
