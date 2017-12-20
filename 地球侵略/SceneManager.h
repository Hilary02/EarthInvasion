#pragma once
#include "Scene_Frame.h"
#include "SoundManager.h"
#include "ISceneManager.h"

enum class scene : unsigned char {
	None,
	Title,
	Game,
	Config,
	Ranking,
	GameOver,
	Clear,
};

/*
�V�[���J�ڋ@�\��񋟂���D
Scene_Frame���p�������N���X�̃|�C���^�������C��������Update��Draw�������s���D
�V�[���ύX��v���������ꍇ�́CChangeScene�֐���p���ė\�������
����Update���������s�����Ƃ��ɃV�[���ύX�����s�����D
�V�[����ǉ��������ۂɂ�scene�񋓑̂ɗ񋓎q��ǉ����āCUpdate�����ɂ��ǉ����s�����ƁD
�����݂���ȊO�̃N���X���ĂԂ��Ƃ��ł��Ă��܂��D�C���^�[�t�F�C�X�ɕύX���s���\��

*/
class SceneManager {
public:
	SceneManager();
	~SceneManager();
	void ChangeScene(scene);
	void Update();
	void Draw();

private:
	Scene_Frame* nowScene;    //�V�[���Ǘ��|�C���^
	scene nextScene;    //���̃V�[���Ǘ��ϐ�
};

//SceneManager.cpp�Œ�`
extern SceneManager SceneM;