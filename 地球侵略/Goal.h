#pragma once
#include "Object.h"
#include "SaveData.h"
#include "IStageBase.h"

class Goal :
	public Object
{
public:
	Goal(int x, int y, int handle, int stageID,IStageBase* stage);
	~Goal();
	int update(const Collision & playerCol);
	void Draw(int drawX, int drawY);

private:
	int stageId;
	SaveData &savedata = SaveData::get_instance();
	IStageBase* Istage;
	int img_ufo[4];
	int counter = 0;
};

