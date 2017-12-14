#pragma once
#include "Scene_Frame.h"
#include "SoundManager.h"


enum class scene : unsigned char {
	None,
	Title,
	Game,
	Config,
	Ranking
};

/*
シーン遷移機能を提供する．
Scene_Frameを継承したクラスのポインタをもち，そこからUpdateとDraw処理を行う．
シーン変更を要求したい場合は，ChangeScene関数を用いて予約をする
次のUpdate処理が実行されるときにシーン変更が実行される．
シーンを追加したい際にはscene列挙体に列挙子を追加して，Update処理にも追加を行うこと．
※現在それ以外のクラスも呼ぶことができてしまう．インターフェイスに変更を行う予定

*/
class SceneManager {
public:
	SceneManager();
	~SceneManager();
	void ChangeScene(scene);
	void Update();
	void Draw();

private:
	Scene_Frame* nowScene;    //シーン管理ポインタ
	scene nextScene;    //次のシーン管理変数
};

//SceneManager.cppで定義
extern SceneManager SceneM;