#pragma once
#include "Scene_Frame.h"
#include <string>
#include "SceneManager.h"
#include "KeyManager.h"

class Scene_Clear :
	public Scene_Frame
{
public:
	Scene_Clear();
	~Scene_Clear();
	void update();
	void Draw();
private:
	std::string text = "StageClear!";
	std::string c_text = "Š®¬”Å‚É‚à‚²Šú‘Ò‚­‚¾‚³‚¢I";

	//ƒNƒ\•Ï”
	int moveto = 200;
	int moveSpeed = 2;
	int y = 0;
	//‚±‚ê‚à‚Ç‚±‚©‚©‚ç‚Á‚Ä‚­‚é
	int Frame = 0;

	bool canDrawButton = false;

	int bg;
};

