#include "SceneHedder.h"
#include "Director.h"
#include "ObjectManager.h"
#include "EffectManager.h"

PlayScene::PlayScene(int mapNum)
{
	const VECTOR Player1InitPos = VGet(-742.0f, 0.0f, 335.0f);
	const VECTOR Player1InitDir = VGet(1.0f, 0.0f, -1.0f);
	const VECTOR Player2InitPos = VGet(742.0f, 0.0f, -355.0f);
	const VECTOR Player2InitDir = VGet(-1.0f, 0.0f, 1.0f);

	// カメラ生成.
	MainCamera* mainCam = new MainCamera;

	// プレイヤー生成.
	int padInput = DX_INPUT_PAD1;
	player[0] = new PlayerBody(Player1InitPos, Player1InitDir, padInput, ObjectTag::Player1, "data/player1/");
	ObjectManager::Entry(player[0]);

	int padInput2 = DX_INPUT_PAD2;
	player[1] = new PlayerBody(Player2InitPos, Player2InitDir, padInput2, ObjectTag::Player2, "data/player2/");
	ObjectManager::Entry(player[1]);


	MapManager* map = new MapManager(mapNum);
	battleNum = 0;
	deltaWaitTime = 0.0f;
}

PlayScene::~PlayScene()
{
}

SceneBase* PlayScene::Update(float deltaTime)
{
	// 全オブジェクトの更新.
	ObjectManager::Update(deltaTime);
	ObjectManager::Collition();

	EffectManager::Update(deltaTime);

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
	EffectManager::Play();
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
