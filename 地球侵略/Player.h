#pragma once
#include "Creature.h"
class Player :
	public Creature
{
public:
	Player();
	~Player();
	void Update();
	void Draw();
};

