#pragma once
/**
マップに配置するアイテムや敵などに必要な情報を管理する．

*/
class Root {
public:
	Root();
	~Root();
	void Update();
	void Draw();

	// マップにおいての絶対座標を指定するとその座標に設定
	void setAbsolutePos(double modX, double modY);
	//移動量を設定すると引数の値を移動した位置へ移動
	void setRelativePos(double modX, double modY);

protected:
	//初期座標
	double defaultX;
	double defaultY;
	//現在座標
	double x;
	double y;
};

