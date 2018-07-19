#pragma once
#include "Scene_Frame.h"
#include "SoundManager.h"

class Scene_Config :
	public Scene_Frame
{
public:
	Scene_Config();
	~Scene_Config();
	void update();
	void Draw();
	// キー入力に応じてコンフィグ操作を行う関数
	void MoveCursor();
private:
private:
	int bg;
	int cursor;
	int volBar;
	const static int MENU_NUM = 3;
	enum OPTION_SELECT {
		BGM, SE, EXIT //オプションメニュー
	};
	enum OPTION_DRAW {
		VOL_CON, KEY_CON   //PADの設定は保留
	};
	//メニューの描画場所と内容をまとめる
	typedef struct {
		int x, y;			// 座標格納用変数
		char name[32];		// 項目名格納用変数
	} MenuElement_t;

	MenuElement_t MenuElement[MENU_NUM] = {	//実際の位置や値の設定
		{ 470, 280, "BGM" },
		{ 470, 340, "SE" },
		{ 470, 400, "Back to Title" }
	};
	int nowSelect;
	int nowDraw;
	bool isKeyConfig = false;
};

