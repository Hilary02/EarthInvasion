#pragma once


//�܂��g��������Ȃ̂ŕۗ�
enum class scene_test : unsigned char {
	None,
	Title,
	Game,
	Config,
	Ranking,
	GameOver,
	Clear,
};



class ISceneManager {
public:
	virtual void ChangeScene(scene_test) = 0;
};