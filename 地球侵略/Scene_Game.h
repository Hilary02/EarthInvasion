#pragma once
#include "Scene_Frame.h"
#include "Stage_Base.h"
#include "SaveData.h"
#include <array>

class Scene_Game :
	public Scene_Frame
{
public:
	Scene_Game(int param=0);
	~Scene_Game();
	void update();
	void Draw();
private:
	typedef struct {
		int x, y;	//起点の座標
		int w, h;	//枠のサイズ
		int requireStage1, requireStage2;	//前提となるステージ
		int U, D, L, R;	//キー入力時の移動先
	}stageFrame;
	stageFrame stageFrameData[14] = {		//どこかで全部定義しとくと実装が楽なんだけどさすがにダメ？
		{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1 }	,
		{ 20,20,135,135,0,0,4,2,1,9 }	,
		{ 20,155,135,135,0,0,1,3,2,9 }	,
		{ 20,310,135,135,9,0,2,4,3,10 }	,
		{ 20,445,135,135,9,0,3,1,4,10 }	,
		{ 310,20,135,135,10,0,8,6,9,11 }	,
		{ 310,155,135,135,10,0,5,7,9,11 }	,
		{ 310,310,135,135,11,0,6,8,10,12 }	,
		{ 310,445,135,135,12,0,7,5,10,12 }	,
		{ 155,20,135,270,1,2,10,10,1,5 }	,
		{ 155,310,135,270,3,4,9,9,3,7 }	,
		{ 445,20,135,270,5,6,12,12,5,13 }	,
		{ 445,310,135,270,7,8,11,11,7,13 }	,
		{ 600,20,180,560,12,0,13,13,11,13 }
	};


	void selectUpdate();
	void selectDraw();
	Stage_Base* nowStage;
	bool stageSelecting = true;
	int nowSelect = 1;
	std::array<int, 14> clearState;
	SaveData &savedata = SaveData::get_instance();
	int bg_stageselect;

	//太枠箱表示関数
	void DrawThickBox(int x1, int y1, int x2, int y2, unsigned int Color, int Thickness = 1);

};

