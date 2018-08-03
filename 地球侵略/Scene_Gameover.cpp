#include "Scene_Gameover.h"

Scene_Gameover::Scene_Gameover(int param) {
	img = LoadGraph("data/img/gameover.png");
	stage = param;
}


Scene_Gameover::~Scene_Gameover() {
	DeleteGraph(img);
}

void Scene_Gameover::update() {
	speed += acceleration;		//�d�͂ŗ�������悤�Ȋ�����
	y += speed;
	if (y >= moveTo) {
		y = moveTo;
		speed *= -0.5;
	}
	if (abs(speed) <= 0.2) canDrawButton = true;
	if (canDrawButton  && keyM.GetKeyFrame(KEY_INPUT_Z)) {
		SceneM.ChangeScene(scene::Select, stage);
	}
}

void Scene_Gameover::Draw() {
	SetFontSize(36);
	DrawGraph(0, y, img, true);

	if (canDrawButton) {
		DrawFormatString(200, 500, 0xFFFFFF, "Z�L�[�ŃX�e�[�W�Z���N�g�ɖ߂�");
	}
	SetFontSize(-1);
}