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


	int keyFrame[256];		// �L�[���̓t���[���ێ�
	char keyStateBuf[256];	// �L�[���͂̃o�b�t�@
};

//KeyManageer.cpp�Œ�`�ς�
//���̃C���X�^���X��p���ċ@�\���g��
extern KeyManager keyM;