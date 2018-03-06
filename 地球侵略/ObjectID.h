#pragma once

enum class ObjectID {
	none = 0,
	soldierA = 4,	//一般兵士
	healPot = 5,	//回復アイテム
	spike = 9,		//とげとげ
	lockedDoor = 6,	//閉じている扉
	moveingFloor = 8,//動く床
	goal = 99,		//ゴール
	playerBullet = 100,	//プレイヤーが撃った弾
	enemyBullet = 104,	//兵士Aが撃った弾
};