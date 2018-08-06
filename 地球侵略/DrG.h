#pragma once
#include "Creature.h"
#include "SaveData.h"
#include "IStageBase.h"

class DrG :
	public Creature
{
public:
	DrG();
	~DrG();
	DrG(int x, int y, int img, ObjectID id, IObjectManager* Iobj, int stageID, IStageBase* stage);
	int update(const Collision & playerCol) override;
	void Draw(int drawX, int drawY) override;

private:
	int img_wait[2];
	int img_damage;
	int img_die[4];
	int counter = 0;


	int spawnTime;
	int invulnerable = 0;
	const int invulnerableTime = 240;
	int deadcounter = 0;

	int stageId;
	SaveData &savedata = SaveData::get_instance();
	IStageBase* Istage;

};

