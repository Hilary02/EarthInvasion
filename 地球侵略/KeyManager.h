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


	int keyFrame[256];		// キー入力フレーム保持
	char keyStateBuf[256];	// キー入力のバッファ
};

//KeyManageer.cppで定義済み
//このインスタンスを用いて機能を使う
extern KeyManager keyM;