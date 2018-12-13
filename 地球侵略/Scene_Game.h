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
	void UpdatePause();
	void DrawPause();
	Stage_Base * nowStage;
	int pauseBgL;
	int pauseBgR;
	bool isPause = false;
	int bgAnimation = 0;
	int select = 0;
	int cursor;
	int selecting = 0;
	int stageID;
};

