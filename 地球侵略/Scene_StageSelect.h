#pragma once
#include "Scene_Frame.h"
#include "SaveData.h"

#include <array>
class Scene_StageSelect :
	public Scene_Frame{
public:
	Scene_StageSelect();
	~Scene_StageSelect();
	void update();
	void Draw();
private:
	int nowSelect = 0;
	std::array<int, 14> clearState;
	SaveData &savedata = SaveData::get_instance();
};

