#pragma once
/**
キーボードの入力状況を管理する
キーコンフィグ関係もここに組み込まれるはず
*/
class KeyManager{
public:
	KeyManager();
	~KeyManager();

	void UpdateKeyState();	//キー入力フレームの更新
	int GetKeyFrame(int);	//キー入力フレームの値を取得

	void KeyConfig(int keyCode);
	bool TabooKey(int keyCode);
	void SwapKey(int roleKey, int keyCode);

	int keyFrame[256];		// キー入力フレーム保持
	char keyStateBuf[256];	// キー入力のバッファ

	//キーコード格納配列
	int keyCodes[8];

	enum keyCode {
		keyInputLeft	//左
		, keyInputRight //右
		, keyInputUp    //上
		, keyInputDown  //下

		, keyInputAttack      //攻撃&決定
		, keyInputParasite    //寄生&キャンセル
		, keyInputEscape      //寄生をやめる
		, keyInputMenu        //メニュー&ポーズ
	};
};

//KeyManageer.cppで定義済み
//このインスタンスを用いて機能を使う
extern KeyManager keyM;