#pragma once
#include "Object.h"

class HealItem :
	public Object
{
public:
	HealItem(int x,int y ,int img);
	~HealItem();
	void Update();
	void Draw();
};

