#pragma once
#include <DxLib.h>
#include "KeyManager.h"

class Scene_Frame
{
public:
	Scene_Frame();
	virtual ~Scene_Frame();
	virtual void Update() = 0;
	virtual void Draw() = 0;
};

#include "SceneManager.h"
