#pragma once
#include "Root.h"
/**
敵や主人公など，キャラクターを管理する．
体力や攻撃力などステータス管理をできるように．
*/
class Creature :
	public Root {
public:
	Creature();
	~Creature();
private:
	int hp;
	int attack;
public:
	// 体力を変更
	void setHp();
	// 攻撃力を設定
	int setAtk();
	// 体力を取得する
	int getHp();
};

