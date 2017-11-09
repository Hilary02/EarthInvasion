#include "Scene_Game.h"
#include "StageSample.h"
#include "Stage_Base.h"



Scene_Game::Scene_Game(){
	nowStage = new Stage_Base;
}


Scene_Game::~Scene_Game(){
	delete nowStage;
}

void Scene_Game::Update(){
	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
	nowStage->update();
	//nowStage->scrollTest();
}

void Scene_Game::Draw(){
	nowStage->draw();
}
