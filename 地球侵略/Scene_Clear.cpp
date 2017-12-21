#include "Scene_Clear.h"



Scene_Clear::Scene_Clear()
{
}


Scene_Clear::~Scene_Clear()
{
}

void Scene_Clear::Update() {
	Frame++;
	if (Frame % 2 == 0 && !canDrawButton) {
		y += moveSpeed;
	}
	if (y == moveto) {
		canDrawButton = true;
		moveSpeed = 0;
	}

	if (canDrawButton  && keyM.GetKeyFrame(KEY_INPUT_Z)) {
		SceneM.ChangeScene(scene::Title);
	}
}

void Scene_Clear::Draw() {
	SetFontSize(30);
	DrawFormatString(200, y, 0xFF0000, text.c_str());

	if (canDrawButton) {
		
		DrawFormatString(200, 270, 0xFFFFFF, c_text.c_str());
		DrawFormatString(200, 300, 0xFFFFFF, "Zキーでタイトルに戻る");
	}
	SetFontSize(16);
}