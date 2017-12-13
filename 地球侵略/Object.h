#pragma once
/**
動く床やアイテムなど，ステージ上に配置されるモノを管理
詳細未定
*/
class Object {
public:
	Object();
	Object(int x, int y, int handle);
	~Object();
	virtual void Update();
	virtual void Draw(int drawX, int drawY);

	// マップにおいての絶対座標を指定するとその座標に設定
	void setAbsolutePos(int modX, int modY);
	//移動量を設定すると引数の値を移動した位置へ移動
	void setRelativePos(int modX, int modY);

protected:
	int x, y;

	int imgHundle;
};
