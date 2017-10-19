#pragma once
#include "Root.h"
/**
動く床やアイテムなど，ステージ上に配置されるモノを管理
詳細未定
*/
class Object :
	public Root {
public:
	Object(int x, int y, char*);
	~Object();
	void Update();
	void Draw();
};

