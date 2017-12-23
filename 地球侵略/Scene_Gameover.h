#pragma once
#include "Scene_Frame.h"
#include <string>
#include "SceneManager.h"
#include "KeyManager.h"

//SceneManager��Singleton�ɂ��悤

class Scene_Gameover :
	public Scene_Frame
{
public:
	Scene_Gameover();
	~Scene_Gameover();
	void update();
	void Draw();

private:
	std::string text = "GameOver...";
	//�N�\�ϐ�
	int moveto = 200;
	int moveSpeed = 2;
	int y = 0;
	//������ǂ������玝���Ă���
	int Frame = 0;

	bool canDrawButton=false;
};

