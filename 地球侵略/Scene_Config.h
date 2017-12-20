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
private:
	const static int MENU_NUM = 5;
	//どれが選択されているのか
	enum OPTION_SELECT {
		BGM, SE, KEY, PAD, EXIT
	};
	enum OPTION_DRAW {
		VOL_CON, KEY_CON, PAD_CON
	};
	//メニューの描画場所と内容をまとめる
	typedef struct {
		int x, y;			// 座標格納用変数
		char name[32];		// 項目名格納用変数
	} MenuElement_t;

	MenuElement_t MenuElement[MENU_NUM] = {	//実際の値の設定
		{ 400, 280, "BGM" },
		{ 400, 310, "SE" },
		{ 400, 340, "KEY" },
		{ 400, 370, "PAD" },
		{ 400, 400, "Back to Title" }
	};
	int nowSelect;
	int nowDraw;
	bool isKeyConfig = false;
public:
	// キー入力に応じてコンフィグ操作を行う関数
	void MoveCursor();
};

