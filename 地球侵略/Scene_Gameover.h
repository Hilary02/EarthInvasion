#pragma once
#include "Scene_Frame.h"
#include <string>
#include "SceneManager.h"
#include "KeyManager.h"

//SceneManager‚ğSingleton‚É‚µ‚æ‚¤

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
	//ƒNƒ\•Ï”
	int moveto = 200;
	int moveSpeed = 1;
	int y = 0;
	//‚±‚ê‚à‚Ç‚±‚©‚©‚ç‚Á‚Ä‚­‚é
	int Frame = 0;

	bool canDrawButton=false;
};

