#pragma once
#include "SceneBase.h"
class SceneManager
{
public:
	~SceneManager();
	static SceneBase* GetInstance()
	{
		static SceneBase* instance;
		return instance;
	}
	void SetScene(SceneBase* scene) { nowScene = scene; }
	int Update(float& deltaTime);
	void Draw();
	class SceneBase* nowScene;
};

#define SCENEINSTANCE SceneBase* GetInstance()