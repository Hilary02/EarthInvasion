/*
08.17　Hilary
Inputだとファイルとかと紛らわしのでKeyに変更．
ここにキ―コンフィグとかもろもろの処理を書いていきたい．
また，どのキーが入力されているのか返すのもここで行う．
*/
#include "KeyManager.h"
#include "DxLib.h"

KeyManager keyM;


KeyManager::KeyManager()
{
}


KeyManager::~KeyManager()
{
}

//キーの入力フレーム数の更新を行う．
//キーコンフィグ機能がついたら更新する必要あり．
void KeyManager::UpdateKeyState() {
	//全てのキーの入力状態を取得
	GetHitKeyStateAll(keyStateBuf);
	for (int i = 0; i < 256; i++)
		keyFrame[i] = keyStateBuf[i] ? ++keyFrame[i] : 0;
}


//キーの入力フレーム数の返却を行う．
int KeyManager::GetKeyFrame(int keyCode) {
	return keyFrame[keyCode];
}
