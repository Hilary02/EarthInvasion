#pragma once
#include <DxLib.h>
/**
動く床やアイテムなど，ステージ上に配置されるモノを管理
詳細未定
*/
class Object {
public:
	Object();
	Object(int x, int y, int handle);
	~Object();
	void Update();
	void Draw();

	// マップにおいての絶対座標を指定するとその座標に設定
	void setAbsolutePos(int modX, int modY);
	//移動量を設定すると引数の値を移動した位置へ移動
	void setRelativePos(int modX, int modY);

	/*
	引数として渡されたObjectと接触判定をとる．
	何らかと接触したときに1を返し，接触しなかった場合に0を返す．
	判定の際に利用する値はx,y,
	*/
	int hitCheck(Object target);
	

protected:
	void onContact();

	int x, y;
	int imgHundle;
	int collisionSize = 0.8;
};
