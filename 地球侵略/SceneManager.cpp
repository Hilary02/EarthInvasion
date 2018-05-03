#include "SceneManager.h"

#include "Scene_Title.h"
#include "Scene_Select.h"
#include "Scene_Game.h"
#include "Scene_Config.h"
#include "Scene_Gameover.h"
#include "Scene_Clear.h"

SceneManager SceneM;

SceneManager::SceneManager() {
	nowScene = new Scene_Title();
	nextScene = scene::Title;
}

SceneManager::~SceneManager()
{
}

void SceneManager::ChangeScene(scene next, int param) {
	this->param = 0;
	nextScene = next;
	this->param = param;
}

void SceneManager::update() {
	if (nextScene != scene::None) {
		delete nowScene;
		switch (nextScene) {
		case scene::Title:
			nowScene = new Scene_Title();
			break;
		case scene::Select:
			nowScene = new Scene_Select(param);
			break;
		case scene::Game:
			nowScene = new Scene_Game(param);
			break;
		case scene::Config:
			nowScene = new Scene_Config();
			break;
		case scene::GameOver:
			nowScene = new Scene_Gameover();
			break;
		case scene::Clear:
			nowScene = new Scene_Clear();
			break;
		}
		nextScene = scene::None;
	}
	nowScene->update();
}

void SceneManager::Draw() {
	nowScene->Draw();
}