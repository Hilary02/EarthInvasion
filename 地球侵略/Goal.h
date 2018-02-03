#pragma once
#include "Object.h"
#include "SaveData.h"

class Goal :
	public Object
{
public:


	Goal(int x, int y, int handle, ICollisionManager* IcolMgr,int stage);
	~Goal();
	int update(const Collision & playerCol);
	void Draw(int drawX, int drawY);

private:
	Collision* collision;
	int stageId;
	SaveData &savedata = SaveData::get_instance();

};

