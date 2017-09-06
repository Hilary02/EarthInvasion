#pragma once
#include "Creature.h"
class Player :
	public Creature
{
public:
	Player();
	Player(int x, int y);
	~Player();
	void Update();
	void Draw();
private:
	double jumpPower = 5.0;
	double speed = 10.0;
	bool canJump;

};

