#pragma once
#include "Scene_Frame.h"
#include "Stage_Base.h"

class Scene_Game :
	public Scene_Frame {
public:
	Scene_Game(int param = 0);
	~Scene_Game();
	void update();
	void Draw();
private:
	Stage_Base * nowStage;
};

