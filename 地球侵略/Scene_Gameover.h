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
	Scene_Gameover();
	~Scene_Gameover();
	void Update();
	void Draw();

private:
	std::string text = "GameOver...";
	//クソ変数
	int moveto = 200;
	int moveSpeed = 2;
	int y = 0;
	//これもどこかから持ってくる
	int Frame = 0;

	bool canDrawButton=false;
};

