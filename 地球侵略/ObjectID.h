#pragma once

enum class ObjectID {
	none = 0, //何もない空間
	inVisibleWall = 1, //見えない壁
	ground = 2, //地面
	colorDifGround = 3, //色違い地面
	spike = 4,		//とげとげ
	spike_flip = 5, //逆とげ
	spark = 6, //ビリビリ
	fire = 7, //炎
	abyss = 9, //奈落（即死）

	movingFloor = 10,//動く床

	difMoveGround = 11,//逆向きに動く地面（仮）
	lockedDoor = 12,	//閉じている扉
	alienLaser = 13, //エイリアンレーザー

	soldierA = 20,	//一般兵士
	ltv = 21,  //中将
	soldierB = 22, //ベテラン兵
	venomMan = 23, //毒人間
	witch = 24, //魔法使い

	healPot = 30,	//回復アイテム
	detoxPot = 31, //解毒薬

	DrG = 40,	//ボス1 Dr.G
	robotEnemy = 41,

	bgmChanger = 91,
	goal = 99,		//ゴール
	playerBullet = 100,	//プレイヤーが撃った弾
	enemyBullet = 104,	//兵士が撃った弾
};