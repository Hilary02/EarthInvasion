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
	std::string c_text = "�����łɂ������҂��������I";

	//�N�\�ϐ�
	int moveto = 200;
	int moveSpeed = 2;
	int y = 0;
	//������ǂ������玝���Ă���
	int Frame = 0;

	bool canDrawButton = false;

	int bg;
};

