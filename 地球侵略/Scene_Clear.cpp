#include "Scene_Clear.h"



Scene_Clear::Scene_Clear(){
	bg = LoadGraph("data/img/clear1.png");
}


Scene_Clear::~Scene_Clear()
{
}

void Scene_Clear::update() {
	Frame++;
	if (Frame % 2 == 0 && !canDrawButton) {
		y += moveto;
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
	DrawGraph(0, 0, bg, true);
	SetFontSize(30);
	

	if (canDrawButton) {
		
		//DrawFormatString(200, 270, 0xFFFFFF, c_text.c_str());
		DrawFormatString(150, 420, 0xFF0000, c_text.c_str());
		DrawFormatString(150, 480, 0xFFFFFF, "Z�L�[�Ń^�C�g���ɖ߂�");
	}
	SetFontSize(16);
}