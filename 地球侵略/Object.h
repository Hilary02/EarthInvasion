#pragma once
#include <DxLib.h>
#include "Collision.h"
#include "ObjectID.h"
#include "IObjectManager.h"

//Enemyなどの管理用に
enum class state {
	none,
	alive,
	dead,
	respawn,
};

/**
動く床やアイテムなど，ステージ上に配置されるモノを管理
詳細未定
*/
class Object {
public:
	Object();
	Object(int x, int y, int handle);
	~Object();
	virtual int update(const Collision & playerCol);
	virtual void Draw(int drawX, int drawY);
	//void collisionCheck();

	// マップにおいての絶対座標を指定するとその座標に設定
	void setAbsolutePos(int modX, int modY);
	//移動量を設定すると引数の値移動する
	void setRelativePos(int modX, int modY);
	ObjectID getId();

	Collision* collision;
	//そのうちprivateに変える
	state state = state::none;

protected:
	//当たり判定の大きさ
	int colXOffset = 0;
	int colYOffset = 0;
	int colXSize = 32;
	int colYSize = 64;
	ObjectID id;

	//座標
	int x, y;

	int imgHandle;
};
