#pragma once
#include "Scene_Frame.h"


enum class scene {
	None,
	Title,
	Game,
	Config,
	Ranking
};

class SceneManager {
public:
	SceneManager();
	~SceneManager();
	void ChangeScene(scene);
	void Update();
	void Draw();

private:
	Scene_Frame* nowScene;    //�V�[���Ǘ��|�C���^
	scene nextScene;    //���̃V�[���Ǘ��ϐ�
};

//SceneManager.cpp�Œ�`
extern SceneManager SceneM;