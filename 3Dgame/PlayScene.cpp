#include "PlayScene.h"

PlayScene::PlayScene()
{
	// カメラ生成.
	/*MainCamera* mainCam = new MainCamera(40, -90);
	ObjectManager::Entry(mainCam);*/
	MainCamera* mainCam = new MainCamera;

	// プレイヤー生成.
	const int playerNum = 2;
	PlayerBody* player[playerNum];
	int padInput = DX_INPUT_PAD1;
	player[0] = new PlayerBody(VGet(-742.0f, 0.0f, 355.0f), VGet(1.0f, 0.0f, -1.0f), padInput, PlayerTag::P1, "data/player1/");
	ObjectManager::Entry(player[0]);

	int padInput2 = DX_INPUT_PAD2;
	player[1] = new PlayerBody(VGet(742.0f, 0.0f, -355.0f), VGet(-1.0f, 0.0f, 1.0f), padInput2, PlayerTag::P2, "data/player2/");
	ObjectManager::Entry(player[1]);

	/*EnemyBody* enemy = new EnemyBody(VGet(742.0f, 0.0f, 355.0f), VGet(0.0f, 0.0f, -1.0f), "data/enemy/");
	ObjectManager::Entry(enemy);*/

	MapManager* map = new MapManager;
}

PlayScene::~PlayScene()
{
}

SceneBase* PlayScene::Update(float deltaTime)
{
	// 全オブジェクトの更新.
	ObjectManager::Update(deltaTime);
	ObjectManager::Collition();

	return this;
}

void PlayScene::Draw()
{
	// 全オブジェクトの描画.
	ObjectManager::Draw();
}
