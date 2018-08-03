#include "Scene_Select.h"

Scene_Select::Scene_Select(int param) {
	int clearedNum = 0;
	savedata.load();
	for (unsigned int i = 0; i < clearState.size(); i++) {
		clearState[i] = savedata.getClearFlag(i);
	}
	//ロードした段階では，クリア済みは1，そうでないものは0となっている．これを挑戦可能なものと不可能なものに分ける．

	clearState[0] = 1;	//挑戦できないステージ．基本的にアクセスしない
	for (unsigned int i = 1; i < clearState.size(); i++) {
		int r1 = stageFrameData[i].requireStage1;
		int r2 = stageFrameData[i].requireStage2;
		if (clearState[i] == 0) {
			if (i >= 9 && i <= 12 && clearState[i - 1] == 1) {
				clearState[i] = 3;	//未クリアのボスステージのうち一番小さいステージを3番に
			}
			if ((clearState[r1] & clearState[r2]) == 1) {	//ビット演算．要求ステージが両方1なら条件を満たす
				clearState[i] = 2;
			}
		}
	}
	/* 0:挑戦不可
	1:クリア済
	2:未クリア(挑戦可)
	3:うっすら表示(直近のボスステージ)
	*/
	bg = LoadGraph("data/img/bg_stageselect.png");
	if (1 <= param && param <= 13) {
		selecting = param;
	}
}


Scene_Select::~Scene_Select() {
	DeleteGraph(bg);
}

void Scene_Select::update() {
	//さほど多くの移動をするわけではないと考え，長押し処理はいったん削除した
	if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || keyM.GetKeyFrame(KEY_INPUT_UP) == 1 || keyM.GetKeyFrame(KEY_INPUT_LEFT) == 1 || keyM.GetKeyFrame(KEY_INPUT_RIGHT) == 1) {
		int nextSelect = 1;
		//if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1 || (keyM.GetKeyFrame(KEY_INPUT_DOWN) >= 15 && keyM.GetKeyFrame(KEY_INPUT_DOWN) % 4 == 0)) {	//下キーが押されていたら
		if (keyM.GetKeyFrame(KEY_INPUT_DOWN) == 1) { nextSelect = stageFrameData[selecting].D; }
		if (keyM.GetKeyFrame(KEY_INPUT_UP) == 1) { nextSelect = stageFrameData[selecting].U; }
		if (keyM.GetKeyFrame(KEY_INPUT_LEFT) == 1) { nextSelect = stageFrameData[selecting].L; }
		if (keyM.GetKeyFrame(KEY_INPUT_RIGHT) == 1) { nextSelect = stageFrameData[selecting].R; }
		if (clearState[nextSelect] == 1 || clearState[nextSelect] == 2) {	//選択できるステージだった場合 
			SoundM.Se("data/mc/pick up.wav");
			selecting = nextSelect;
		}
	}

	if (keyM.GetKeyFrame(KEY_INPUT_ESCAPE) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
	if (keyM.GetKeyFrame(KEY_INPUT_Z) == 1) {
		SceneM.ChangeScene(scene::Game, selecting);
	}
	if (keyM.GetKeyFrame(KEY_INPUT_X) == 1) {
		SceneM.ChangeScene(scene::Title);
	}
}

void Scene_Select::Draw()
{
	DrawGraph(0, 0, bg, TRUE);
	int textColor = 0x000000;
	for (unsigned int i = 0; i < clearState.size(); i++) {
		switch (clearState[i]) {
		case 0:
			textColor = 0x909090; //挑戦不可能
			break;
		case 1:
			textColor = 0xFF0000; //クリア済
			break;
		case 2:
			textColor = 0xFFFFFF; //挑戦可能
			break;
		default:
			textColor = 0x0000FF;	//なんかの例外
			break;
		}
		//DrawFormatString(150, i * 20, textColor, "Stage%d", i);
	}
	//DrawFormatString(120, nowSelect * 20, 0xFFFFFF, "◇");

	//仮
	int col_blk = 0x000000;
	int col_blue = 0x0000FF;
	int col_red = 0xFF0000;
	int col_yel = 0xFFFF00;

	clsDx();
	for (int i = 1; i <= 13; i++) {
		printfDx("%d,", clearState[i]);
		int bx = stageFrameData[i].x;
		int by = stageFrameData[i].y;
		int color = col_blk;
		switch (clearState[i]) {
		case 0:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 220);	//かなり濃い
			color = col_blk;
			break;
		case 1:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);	//薄い
			color = col_yel;
			break;
		case 2:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);	//結構見える
			color = col_blue;
			break;
		case 3:
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);	//うっすらと
			color = col_blk;
			break;
		default:
			color = 0xFF00FF;
			break;
		}

		DrawBox(bx, by, bx + stageFrameData[i].w, by + stageFrameData[i].h, color, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	int bx = stageFrameData[selecting].x;
	int by = stageFrameData[selecting].y;
	DrawThickBox(bx, by, bx + stageFrameData[selecting].w, by + stageFrameData[selecting].h, 0xFF0000, 3);
}

void Scene_Select::DrawThickBox(int x1, int y1, int x2, int y2, unsigned int Color, int Thickness) {
	DrawLine(x1, y1, x1, y2, Color, Thickness);
	DrawLine(x1, y2, x2, y2, Color, Thickness);
	DrawLine(x2, y2, x2, y1, Color, Thickness);
	DrawLine(x2, y1, x1, y1, Color, Thickness);
}
