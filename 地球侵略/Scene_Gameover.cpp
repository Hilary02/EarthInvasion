#include "Scene_Gameover.h"

Scene_Gameover::Scene_Gameover() {
	img = LoadGraph("data/img/gameover.png");
}


Scene_Gameover::~Scene_Gameover() {
	DeleteGraph(img);
}

void Scene_Gameover::update() {
	speed += acceleration;		//重力で落下するような感じに
	y += speed;
	if (y >= moveTo) {
		y = moveTo;
		speed *= -0.5;
	}
	if (abs(speed) <= 0.2) canDrawButton = true;
	if (canDrawButton  && keyM.GetKeyFrame(KEY_INPUT_Z)) {
		SceneM.ChangeScene(scene::Title);
	}
}

void Scene_Gameover::Draw() {
	SetFontSize(36);
	DrawGraph(0, y, img, true);

	if (canDrawButton) {
		DrawFormatString(200, 300, 0xFFFFFF, "Zキーでタイトルに戻る");
	}
	SetFontSize(-1);
}