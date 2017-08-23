/*
08.17�@Hilary
Input���ƃt�@�C���Ƃ��ƕ���킵�̂�Key�ɕύX�D
�����ɃL�\�R���t�B�O�Ƃ��������̏����������Ă��������D
�܂��C�ǂ̃L�[�����͂���Ă���̂��Ԃ��̂������ōs���D
*/
#include "KeyManager.h"
#include "DxLib.h"

KeyManager keyM;


KeyManager::KeyManager() {
	int keyData[] = { KEY_INPUT_LEFT,	KEY_INPUT_RIGHT,  KEY_INPUT_UP,
		KEY_INPUT_DOWN,	KEY_INPUT_A,	  KEY_INPUT_S,
		KEY_INPUT_E,	KEY_INPUT_ESCAPE };

	//FILE *fp = fopen("keyData.dat", "rb");			//�o�C�i���t�@�C�����J��

	////�t�@�C���ɕۑ�����Ă����L�[�R�[�h�����蓖��
	//if (fp != NULL) {
	//	fread(&keyData, sizeof(keyData), 1, fp);
	//	fclose(fp);
	//}
	//�L�[�R�[�h
	for (int i = 0; i < 8; i++) {
		keyCodes[i] = keyData[i];
	}
}


KeyManager::~KeyManager()
{
}

//�L�[�̓��̓t���[�����̍X�V���s���D
//�L�[�R���t�B�O�@�\��������X�V����K�v����D
void KeyManager::UpdateKeyState() {
	//�S�ẴL�[�̓��͏�Ԃ��擾
	GetHitKeyStateAll(keyStateBuf);
	for (int i = 0; i < 256; i++)
		keyFrame[i] = keyStateBuf[i] ? ++keyFrame[i] : 0;
}


//�L�[�̓��̓t���[�����̕ԋp���s���D
int KeyManager::GetKeyFrame(int keyCode) {
	return keyFrame[keyCode];
}


void KeyManager::KeyConfig(int keyCode) {
	//if(CheckHitKeyAll() == 0) return false;		// �L�[�����ׂė������܂�false��Ԃ�


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


// �֎~�L�[
bool KeyManager::TabooKey(int keyCode) {	// �L�[�ύX�Ɏg���Ȃ��L�[�̏ꍇtrue��Ԃ�
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