#include "Scene_Game.h"
#include "StageSample.h"

//StageSample stage1;
StageSample* nowStage;

Scene_Game::Scene_Game(){
	nowStage = new StageSample;
	nowStage->initMap();
}


Scene_Game::~Scene_Game(){
	delete nowStage;
}

void Scene_Game::Update(){
	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
	nowStage->scrollTest();
}

void Scene_Game::Draw(){
	DrawString(0, 0, "�Q�[��(�f�o�b�O�\���j", 0xFFFFFF);
	nowStage->drawMap();
}
