#pragma once
#include "Scene_Frame.h"
#include <string>
#include "SceneManager.h"
#include "KeyManager.h"

//SceneManagerをSingletonにしよう

class Scene_Gameover :
	public Scene_Frame
{
public:
	Scene_Gameover(int param = 0);
	~Scene_Gameover();
	void update();
	void Draw();

private:
	std::string text = "GameOver...";
	int moveTo = 0;
	double speed = 0.6;
	double acceleration = 0.5;
	int y = -600;
	int img;
	//これもどこかから持ってくる
	int Frame = 0;
	int stage = 0;

	bool canDrawButton = false;
};

