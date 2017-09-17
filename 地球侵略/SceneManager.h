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
	Scene_Frame* nowScene;    //シーン管理ポインタ
	scene nextScene;    //次のシーン管理変数
};

//SceneManager.cppで定義
extern SceneManager SceneM;