#include "SceneManager.h"

#include "Scene_Config.h"
#include "Scene_Game.h"
#include "Scene_Title.h"



SceneManager SceneM;

SceneManager::SceneManager() :
	nextScene(scene::None) {
	nowScene = new Scene_Title();
	//nowScene = (Scene_Frame*) new Scene_Title();
}


SceneManager::~SceneManager()
{
}

void SceneManager::ChangeScene(scene next) {
	nextScene = next;
}

void SceneManager::Update() {
	if (nextScene != scene::None) {
		delete nowScene;
		switch (nextScene) {
		case scene::Title:
			nowScene = new Scene_Title();
			break;
		case scene::Game:
			nowScene = new Scene_Game();
			break;
		case scene::Config:
			nowScene = new Scene_Config();
			break;
		case scene::Ranking:
			//‚È‚Á‚µ‚ñ
			break;
		}
		nextScene = scene::None;
	}
	nowScene->Update();
}

void SceneManager::Draw() {
	nowScene->Draw();
}
