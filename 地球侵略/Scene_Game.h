#pragma once
#include "Scene_Frame.h"
#include "Stage_Base.h"
#include "SaveData.h"
#include <array>

class Scene_Game :
	public Scene_Frame
{
public:
	Scene_Game();
	~Scene_Game();
	void update();
	void Draw();
private:
	void selectUpdate();
	void selectDraw();
	Stage_Base* nowStage;
	bool stageSelecting = true;
	int nowSelect = 1;
	std::array<int, 14> clearState;
	SaveData &savedata = SaveData::get_instance();
};

