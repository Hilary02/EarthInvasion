/*
08.17�@Hilary
Input���ƃt�@�C���Ƃ��ƕ���킵�̂�Key�ɕύX�D
�����ɃL�\�R���t�B�O�Ƃ��������̏����������Ă��������D
�܂��C�ǂ̃L�[�����͂���Ă���̂��Ԃ��̂������ōs���D
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
