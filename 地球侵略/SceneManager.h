#pragma once
#include "Scene_Frame.h"
#include "SoundManager.h"
#include "ISceneManager.h"

enum class scene : unsigned char {
	None,
	Title,
	Select,
	Game,
	Config,
	GameOver,
	Clear,
};

/*
�V�[���J�ڋ@�\��񋟂���D
Scene_Frame���p�������N���X�̃|�C���^�������C��������update��Draw�������s���D
�V�[���ύX��v���������ꍇ�́CChangeScene�֐���p���ė\�������
����update���������s�����Ƃ��ɃV�[���ύX�����s�����D
�V�[����ǉ��������ۂɂ�scene�񋓑̂ɗ񋓎q��ǉ����āCupdate�����ɂ��ǉ����s�����ƁD
�����݂���ȊO�̃N���X���ĂԂ��Ƃ��ł��Ă��܂��D�C���^�[�t�F�C�X�ɕύX���s���\��
*/
class SceneManager {
public:
	SceneManager();
	~SceneManager();
	void ChangeScene(scene, int param = 0);
	void update();
	void Draw();

private:
	Scene_Frame * nowScene;    //�V�[���Ǘ��|�C���^
	scene nextScene;    //���̃V�[���Ǘ��ϐ�
	int param = 0;
};

//SceneManager.cpp�Œ�`
extern SceneManager SceneM;