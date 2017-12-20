#pragma once
#include "Object.h"
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
	virtual void modHp(int mod);
	// 攻撃力を設定
	void setAtk();
	// 体力を取得する
	int getHp();
	virtual void Update(const Collision & playerCol) override;
	virtual void Draw(int ,int) override;
};

