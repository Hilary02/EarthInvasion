#include "Scene_Gameover.h"



Scene_Gameover::Scene_Gameover()
{
}


Scene_Gameover::~Scene_Gameover()
{
}

void Scene_Gameover::Update(){
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
	DrawFormatString(200, y, 0xFF0000, text.c_str());

	if (canDrawButton) {
		DrawFormatString(200, 300, 0x0000FF, "ƒ^ƒCƒgƒ‹‚É–ß‚é");
	}
}