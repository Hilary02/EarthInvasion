#include "SceneManager.h"

#include "Scene_Config.h"
#include "Scene_Game.h"
#include "Scene_Title.h"
#include "Scene_Gameover.h"
#include "Scene_Clear.h"

SceneManager SceneM;
bool sceneFlag;

SceneManager::SceneManager() :
	nextScene(scene::None) {
	nowScene = new Scene_Title();
	sceneFlag = true;
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
		/*シーンがタイトルならばインスタンスを削除する代わりにタイトルフラグを折るだけ．
		タイトルのカーソル位置を保持するようにするためこうしているが，
		選択位置管理クラスを作るかでメモリ使用量を減らしてもいいかも
		*/
		if (sceneFlag == true) {
			sceneFlag = false;
		}
		else {
			delete nowScene;
		}

		switch (nextScene) {
		case scene::Title:
			nowScene = new Scene_Title();
			sceneFlag = true;
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
		case scene::Ranking:
			//なっしん
			break;
		}
		nextScene = scene::None;
	}
	nowScene->Update();
}

void SceneManager::Draw() {
	nowScene->Draw();
}