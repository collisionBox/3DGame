#include "PlayScene.h"

PlayScene::PlayScene(int mapNum)
{
	// カメラ生成.
	/*MainCamera* mainCam = new MainCamera(40, -90);
	ObjectManager::Entry(mainCam);*/
	MainCamera* mainCam = new MainCamera;

	// プレイヤー生成.
	int padInput = DX_INPUT_PAD1;
	player[0] = new PlayerBody(VGet(-742.0f + 600, 0.0f, -30.0f), VGet(1.0f, 0.0f, 0.0f), padInput, ObjectTag::Player1, "data/player1/");
	ObjectManager::Entry(player[0]);

	int padInput2 = DX_INPUT_PAD2;
	player[1] = new PlayerBody(VGet(742.0f, 0.0f, -355.0f), VGet(-1.0f, 0.0f, 1.0f), padInput2, ObjectTag::Player2, "data/player2/");
	ObjectManager::Entry(player[1]);

	/*EnemyBody* enemy = new EnemyBody(VGet(742.0f, 0.0f, 355.0f), VGet(0.0f, 0.0f, -1.0f), "data/enemy/");a
	ObjectManager::Entry(enemy);*/

	MapManager* map = new MapManager(mapNum);
	battleNum = 0;
	deltaWaitTime = 0.0f;
}

PlayScene::~PlayScene()
{
}

SceneBase* PlayScene::Update(float deltaTime)
{
	EffectManager::Update(deltaTime);
	// 全オブジェクトの更新.
	ObjectManager::Update(deltaTime);
	ObjectManager::Collition();

	if (CheckHitKey(KEY_INPUT_TAB))
	{
		for (int i = 0; i < PlayerNum; i++)
		{
			if (player[i]->GetHP() <= 0)
			{
				CheckWinner();
			}
			deltaWaitTime = 0.0f;
			
		}

	}
	for (int i = 0; i < PlayerNum; i++)
	{
		if (player[i]->GetHP() <= 0)
		{
			CheckWinner();
			PlayerInit();
			deltaWaitTime = 0.0f;
		}
		
	}
	if (IsChangeResultScene())
	{
		DIRECTORINSTANCE.OrderChangeScene(new PlayScene(1));
	}
	return this;
}

void PlayScene::Draw()
{
	// 全オブジェクトの描画.
	ObjectManager::Draw();
	EffectManager::Draw();
}

void PlayScene::CheckWinner()
{
	for (int i = 0; i < PlayerNum; i++)
	{
		if (player[i]->GetHP() > 0)
		{
			player[i]->AddWinNum();
			battleNum += 1;
		}
	}
}

bool PlayScene::IsChangeResultScene()
{
	for (int i = 0; i < PlayerNum; i++)
	{
		if (player[i]->GetWinNum() == maxWinNum || battleNum == maxBattleNum)
		{
			int a = player[i]->GetWinNum();
			return true;
		}
	}
	return false;
}

bool PlayScene::WaitChangeSceneTime(float deltaTime)
{
	if (deltaWaitTime >= OnShootingDownWaitTime)
	{
		return true;
	}
	return false;

}

void PlayScene::PlayerInit()
{
	for (int i = 0; i < PlayerNum; i++)
	{
		player[i]->Initialize();
	}
}
