#pragma once

enum class Action{
	DmgPlayer,
	KillPlayer,
};


class ICollisionManager
{
	//private:
	//	virtual ~iHitAction() {}
public:
	virtual void requestAction(Action act) = 0;
};
