#pragma once
/**
�L�[�{�[�h�̓��͏󋵂��Ǘ�����
�L�[�R���t�B�O�֌W�������ɑg�ݍ��܂��͂�
*/
class KeyManager{
public:
	KeyManager();
	~KeyManager();

	void UpdateKeyState();	//�L�[���̓t���[���̍X�V
	int GetKeyFrame(int);	//�L�[���̓t���[���̒l���擾

	void KeyConfig(int keyCode);
	bool TabooKey(int keyCode);
	void SwapKey(int roleKey, int keyCode);

	int keyFrame[256];		// �L�[���̓t���[���ێ�
	char keyStateBuf[256];	// �L�[���͂̃o�b�t�@

	//�L�[�R�[�h�i�[�z��
	int keyCodes[8];

	enum keyCode {
		keyInputLeft	//��
		, keyInputRight //�E
		, keyInputUp    //��
		, keyInputDown  //��

		, keyInputAttack      //�U��&����
		, keyInputParasite    //��&�L�����Z��
		, keyInputEscape      //�񐶂���߂�
		, keyInputMenu        //���j���[&�|�[�Y
	};
};

//KeyManageer.cpp�Œ�`�ς�
//���̃C���X�^���X��p���ċ@�\���g��
extern KeyManager keyM;