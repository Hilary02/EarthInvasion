#pragma once
#include "Scene_Frame.h"
#include "SaveData.h"
#include <array>

constexpr int stage_num = 10;

class Scene_Select :
	public Scene_Frame
{
public:
	Scene_Select(int param = 0);
	~Scene_Select();
	void update();
	void Draw();
private:
	int bg;
	int over;
	int eeyan;
	int cursor;
	int selecting = 1;
	std::array<int, stage_num + 1> clearState;
	SaveData &savedata = SaveData::get_instance();

	//太枠箱表示関数
	void DrawThickBox(int x1, int y1, int x2, int y2, unsigned int Color, int Thickness = 1);


	typedef struct {
		int x, y;	//起点の座標
		//int w, h;	//枠のサイズ
		int requireStage1, requireStage2;	//前提となるステージ
		int U, D, L, R;	//キー入力時の移動先
	}stageFrame;

	stageFrame stageFrameData[11] = {		//どこかで全部定義しとくと実装が楽なんだけどさすがにダメ？
{-1,-1,-1,-1,-1,-1,-1,-1}	,
{45,350,0,0,1,3,1,2}	,
{160,350,1,0,2,4,1,5}	,
{45,450,0,0,1,3,3,4}	,
{160,450,3,0,2,3,4,5}	,
{280,404,2,4,5,5,2,6}	,
{430,350,5,0,6,8,5,7}	,
{550,350,6,0,7,9,6,10}	,
{430,450,5,0,6,8,5,9}	,
{550,450,8,0,7,9,8,10}	,
{667,409,7,9,10,10,7,10}	,
	};
};

