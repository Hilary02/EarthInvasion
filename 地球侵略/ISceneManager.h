#pragma once


//‚Ü‚¾Žg‚¤‚©–¢’è‚È‚Ì‚Å•Û—¯
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