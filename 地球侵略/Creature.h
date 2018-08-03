#pragma once
#include "Object.h"
//#include "IObjectManager.h"

/**
敵や主人公など，キャラクターを管理する．
体力や攻撃力などステータス管理をできるように．
*/
class Creature :
	public Object {
public:
	Creature();
	~Creature();
protected:
	int hp;
	int attack;
public:
	// 体力を変更
	virtual void setHp(int newHp);
	virtual void modHp(int mod, bool through = false);
	// 攻撃力を設定(これも継承させた) byJ
	virtual void setAtk(int newAtk);
	//攻撃力を取得
	virtual int getAtk();
	// 体力を取得する
	int getHp();

	virtual int update(const Collision & playerCol) override;
	virtual void Draw(int, int) override;
	//地形との当たり判定に用いるインターフェース
	IObjectManager* IobjMgr;

};

