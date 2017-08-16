#pragma once
class Root
{
public:
	Root();
	~Root();

private:
	// 座標
	double defaultX;
	double defaultY;
	double x;
	double y;
public:
	// マップにおいての絶対座標を指定するとその座標に設定
	void setPos(double modX, double modY);
};

