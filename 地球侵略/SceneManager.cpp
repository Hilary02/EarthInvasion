#include "SceneManager.h"

#include "Scene_Title.h"
#include "Scene_StageSelect.h"
#include "Scene_Game.h"
#include "Scene_Config.h"
#include "Scene_Gameover.h"
#include "Scene_Clear.h"

SceneManager SceneM;
bool sceneFlag = false;

SceneManager::SceneManager() :
	nextScene(scene::None) {
	nowScene = new Scene_Title();
	//sceneFlag = true;
	//nowScene = (Scene_Frame*) new Scene_Title();
}

SceneManager::~SceneManager()
{
}

void SceneManager::ChangeScene(scene next) {
	nextScene = next;
}

void SceneManager::update() {
	if (nextScene != scene::None) {
		/*�V�[�����^�C�g���Ȃ�΃C���X�^���X���폜�������Ƀ^�C�g���t���O��܂邾���D
		�^�C�g���̃J�[�\���ʒu��ێ�����悤�ɂ��邽�߂������Ă��邪�C
		�I���ʒu�Ǘ��N���X����邩�Ń������g�p�ʂ����炵�Ă���������
		*/

		//if (sceneFlag == true) {
		//	sceneFlag = false;
		//}
		//else {
		//}
		delete nowScene;

		switch (nextScene) {
		case scene::Title:
			nowScene = new Scene_Title();
			//sceneFlag = true;
			break;
		case scene::StageSelect:
			nowScene = new Scene_StageSelect();
			break;
		case scene::Game:
			nowScene = new Scene_Game();
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