#include "SceneManager.h"

SceneManager::~SceneManager()
{
}

int SceneManager::Update(float& deltaTime)
{
	// �V�[����������ΏI������.
	if (!nowScene)
	{
		return 0;
	}

	SceneBase* tmpScene;// �X�V����V�[��.
	// �X�V.
	tmpScene = nowScene->Update(deltaTime);
	
	//�X�V���Ă���V�[���Ɛݒ肳�ꂽ�V�[�����Ⴏ���.
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
