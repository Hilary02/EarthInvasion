#pragma once
/**
オプション画面の処理を行う．
オプションのセーブ機能がまだないのでやらなきゃいけない
*/
class Option {
public:
	Option();
	~Option();
	void Update();
	void Draw();
private:
	const static int MENU_NUM=5;
	// 音楽ハンドル
	int bgm;
	int se;
	int *music;
	// 音量
	int bgmVolume;
	int seVolume;
	int *volume;

	//どれが選択されているのか
	enum OPTION_SELECT {
		BGM, SE, KEY, PAD, EXIT
	};
	enum OPTION_DRAW {
		VOL_CON,KEY_CON,PAD_CON
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
	bool isKeyConfig=false;
public:
	// キー入力に応じてコンフィグ操作を行う関数
	void MoveCursor();
	void init();
};

extern Option option;