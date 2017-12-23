#pragma once
#include "Scene_Frame.h"
class Scene_Title :
	public Scene_Frame
{
public:
	Scene_Title();
	~Scene_Title();
	void update();
	void Draw();
private:
	int bg;
};

