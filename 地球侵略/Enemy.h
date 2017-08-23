#pragma once
#include "Creature.h"
class Enemy :
	public Creature
{
public:
	Enemy();
	~Enemy();
	void Update();
	void Draw();
};

