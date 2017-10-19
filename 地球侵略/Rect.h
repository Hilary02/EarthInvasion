#pragma once
class Rect
{
public:
	Rect(int, int, int, int);
	Rect();
	~Rect();
	//左上座標Xの取得
	int getLeftX();
	//左上座標Yの取得
	int getLeftY();
	//矩形の幅を取得
	int getWidth();
	//矩形の高さを取得
	int getHeight();
	//あたり判定
	bool isHit(Rect);
private:
	int leftX, leftY, width, height;



};

