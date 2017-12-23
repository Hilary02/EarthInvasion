#include "Scene_Gameover.h"



Scene_Gameover::Scene_Gameover()
{
}


Scene_Gameover::~Scene_Gameover()
{
}

void Scene_Gameover::update(){
	Frame++;
	if (Frame % 2 == 0 && !canDrawButton) {
		y += moveSpeed;
	}
	if (y==moveto) {
		canDrawButton = true;
		moveSpeed = 0;
	}

	if (canDrawButton  && keyM.GetKeyFrame(KEY_INPUT_Z)) {
		SceneM.ChangeScene(scene::Title);
	}
}

void Scene_Gameover::Draw(){
	SetFontSize(30);
	DrawFormatString(200, y, 0xFF0000, text.c_str());

	if (canDrawButton) {
		DrawFormatString(200, 300, 0xFFFFFF, "Zキーでタイトルに戻る");
	}
	SetFontSize(16);
}