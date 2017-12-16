#pragma once

enum class ColAction{
	DmgPlayer,
	KillPlayer,
};


class ICollisionManager
{
	//private:
	//	virtual ~iHitAction() {}
public:
	virtual void requestAction(ColAction act) = 0;
};
