#pragma once
#include "Enemy.h"
#include "SaveData.h"
#include "IStageBase.h"

class Witch :
	public Enemy
{
public:
	Witch(int x, int y, int img, IObjectManager* Iobj, int stageID, IStageBase* stage);
	~Witch();
	void Draw(int drawX, int drawY) override;
	void floating();
	void risingOrDescent();
	void collsionCheck(const Collision & target);
	void attack();
	int update(const Collision & playerCol) override;

private:
	int moveHandle[8];
	int bulletHandle;
	int targetY;
	int targetX;
	int basePositionY;

	bool isPositionY;
	bool isUnderTarget;
	bool isFound = false;
	bool isUnder = false;

	int stageId;
	SaveData &savedata = SaveData::get_instance();
	IStageBase* Istage;

};

