#include "OverScene.h"

SceneBase* OverScene::Update(float deltaTime)
{
	ObjectManager::ReleseAllObj();
	return new PlayScene;

}

void OverScene::Draw()
{
}
