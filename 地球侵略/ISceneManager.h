#pragma once


//まだ使うか未定なので保留
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