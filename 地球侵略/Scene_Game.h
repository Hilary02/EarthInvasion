#pragma once
#include "Scene_Frame.h"
#include "Stage_Base.h"
class Scene_Game :
	public Scene_Frame
{
public:
	Scene_Game();
	~Scene_Game();
	void Update();
	void Draw();
private:
	Stage_Base* nowStage;
};

