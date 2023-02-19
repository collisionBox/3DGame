#include "SceneManager.h"

SceneManager::~SceneManager()
{
}

int SceneManager::Update(float& deltaTime)
{
	// シーンが無ければ終了する.
	if (!nowScene)
	{
		return 0;
	}

	SceneBase* tmpScene;// 更新するシーン.
	// 更新.
	tmpScene = nowScene->Update(deltaTime);
	
	//更新しているシーンと設定されたシーンが違ければ.
	if (tmpScene != nowScene)
	{
		delete nowScene;
		nowScene = tmpScene;
		return 1;
	}
	return 0;
}

void SceneManager::Draw()
{
	if (!nowScene)
	{
		return;
	}
	nowScene->Draw();
}
