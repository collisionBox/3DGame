#include "PlayScene.h"

PlayScene::PlayScene()
{
	// �J��������.
	/*MainCamera* mainCam = new MainCamera(40, -90);
	ObjectManager::Entry(mainCam);*/
	MainCamera* mainCam = new MainCamera;

	// �v���C���[����.
	int padInput = DX_INPUT_PAD1;
	PlayerBody* player = new PlayerBody(VGet(-742.0f + 600, 0.0f, -30.0f), VGet(1.0f, 0.0f, 0.0f), padInput, ObjectTag::Player, "data/player1/");
	ObjectManager::Entry(player);

	int padInput2 = DX_INPUT_PAD2;
	PlayerBody* player2 = new PlayerBody(VGet(742.0f, 0.0f, -355.0f), VGet(-1.0f, 0.0f, 1.0f), padInput2, ObjectTag::Player, "data/player2/");
	ObjectManager::Entry(player2);

	/*EnemyBody* enemy = new EnemyBody(VGet(742.0f, 0.0f, 355.0f), VGet(0.0f, 0.0f, -1.0f), "data/enemy/");a
	ObjectManager::Entry(enemy);*/

	MapManager* map = new MapManager;
}

PlayScene::~PlayScene()
{
}

SceneBase* PlayScene::Update(float deltaTime)
{
	// �S�I�u�W�F�N�g�̍X�V.
	ObjectManager::Update(deltaTime);
	ObjectManager::Collition();
	return this;
}

void PlayScene::Draw()
{
	// �S�I�u�W�F�N�g�̕`��.
	ObjectManager::Draw();
}
