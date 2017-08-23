/*
08.17　Hilary
Inputだとファイルとかと紛らわしのでKeyに変更．
ここにキ―コンフィグとかもろもろの処理を書いていきたい．
また，どのキーが入力されているのか返すのもここで行う．
*/
#include "KeyManager.h"
#include "DxLib.h"

KeyManager keyM;


KeyManager::KeyManager() {
	int keyData[] = { KEY_INPUT_LEFT,	KEY_INPUT_RIGHT,  KEY_INPUT_UP,
		KEY_INPUT_DOWN,	KEY_INPUT_A,	  KEY_INPUT_S,
		KEY_INPUT_E,	KEY_INPUT_ESCAPE };

	//FILE *fp = fopen("keyData.dat", "rb");			//バイナリファイルを開く

	////ファイルに保存されていたキーコードを割り当て
	//if (fp != NULL) {
	//	fread(&keyData, sizeof(keyData), 1, fp);
	//	fclose(fp);
	//}
	//キーコード
	for (int i = 0; i < 8; i++) {
		keyCodes[i] = keyData[i];
	}
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


void KeyManager::KeyConfig(int keyCode) {
	//if(CheckHitKeyAll() == 0) return false;		// キーがすべて離されるまでfalseを返す


	for (int i = 0; i<256; i++) {
		if (GetKeyFrame(i) == 1) {
			if (keyCode == keyInputAttack) {
				if (!TabooKey(i)) {
					SwapKey(keyInputAttack, i);
					keyCodes[keyInputAttack] = i;
				}
			}
		}
	}




}


// 禁止キー
bool KeyManager::TabooKey(int keyCode) {	// キー変更に使えないキーの場合trueを返す
	switch (keyCode) {
	case KEY_INPUT_UP:
	case KEY_INPUT_DOWN:
	case KEY_INPUT_RIGHT:
	case KEY_INPUT_LEFT:
		return true;
	default:
		return false;
	}
}

void KeyManager::SwapKey(int roleKey, int keyCode) {};