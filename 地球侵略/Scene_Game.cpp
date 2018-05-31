#include "Scene_Game.h"
#include "SceneManager.h"
#include "KeyManager.h"

Scene_Game::Scene_Game(int param) {
	nowStage = new Stage_Base(param);
}

Scene_Game::~Scene_Game() {
	delete nowStage;
}

void Scene_Game::update() {
	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
	nowStage->update();
}

void Scene_Game::Draw() {
	nowStage->draw();
}