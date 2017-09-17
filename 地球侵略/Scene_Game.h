#pragma once
#include "Scene_Frame.h"
class Scene_Game :
	public Scene_Frame
{
public:
	Scene_Game();
	~Scene_Game();
	void Update();
	void Draw();
};

