#pragma once
#define MENU_NUM 5

class Option {
public:
	Option();
	~Option();
	void Update();
	void Draw();
private:
	// 音楽ハンドル
	int bgm;
	int se;
	int *music;
	// 音量
	int bgmVolume;
	int seVolume;
	int *volume;
	// フラグ
	bool moveDown;
	bool moveUp;

	enum OPTION_SELECT {
		BGM, SE, KEY, PAD, EXIT
	};
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
public:
	// キー入力に応じてコンフィグ操作を行う関数
	void MoveCursor();
	void init();
};

extern Option option;