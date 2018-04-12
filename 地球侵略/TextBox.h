#pragma once
#include "Object.h"
#include <string>
class TextBox :
	public Object {
public:
	TextBox();
	~TextBox();
	int update(const Collision & playerCol);
	void Draw(int drawX, int drawY);

	int colSizeX;
	int colSizeY;
	int icon;
	std::string text;



};

