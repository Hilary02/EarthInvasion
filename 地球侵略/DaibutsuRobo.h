#pragma once
#include "Creature.h"
#include "SaveData.h"
#include "IStageBase.h"

class DaibutsuRobo :
	public Creature
{
public:
	DaibutsuRobo();
	DaibutsuRobo(int x, int y, int img, ObjectID id, IObjectManager* Iobj, int stageID, IStageBase* stage);
	~DaibutsuRobo();
	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;

private:
	//int img_wait[2];
	int img_body;
	int img_head;

	int stageId;
	SaveData &savedata = SaveData::get_instance();
	IStageBase* Istage;
};

