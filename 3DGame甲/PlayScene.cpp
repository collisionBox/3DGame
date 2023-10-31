#include "PlayScene.h"
#include "ObjectManager.h"
#include "EffectManager.h"
#include "EndScene.h"
#include "Director.h"

PlayScene::PlayScene(int mapNum)
{
	imgHandle = LoadGraph("data/floor.jpg");

	ObjectManager::ReleseAllObj();

	//　マップマネージャの生成.
	MapManager* map = new MapManager(mapNum);

	// カメラ生成.
	MainCamera* mainCam = new MainCamera;

	// プレイヤー生成.
	int padInput = DX_INPUT_PAD1;
	player[0] = new PlayerBody(map->GetSpawnPos(0), VGet(1.0f, 0.0f, 0.0f), padInput, ObjectTag::Player1, "data/player1/");
	ObjectManager::Entry(player[0]);

	/*int padInput2 = DX_INPUT_PAD2;
	player[1] = new PlayerBody(Player2InitPos, Player2InitDir, padInput2, ObjectTag::Player2, "data/player2/");
	ObjectManager::Entry(player[1]);*/

	for (int i = 1; i < map->GetSizeSpawnPosVector(); i++)
	{
		enemy = new EnemyBody(map->GetSpawnPos(i), VGet(1.0f, 0.0f, 0.0f));
		ObjectManager::Entry(enemy);
	}

	battleNum = 0;
	deltaWaitTime = 0.0f;

	fontHandle = CreateFontToHandle(NULL, fontSize, fontThick);
	str = "Ready";

}

PlayScene::~PlayScene()
{
}

SceneBase* PlayScene::Update(float deltaTime)
{
#if 0
	if (deltaWaitTime < WaitingTimeBeforStart)
	{
		deltaWaitTime += deltaTime;
		str = "Ready";
	}
	else
#endif
	{

		if (deltaWaitTime < WaitingTimeBeforStart + StringDrawTime)
		{
			str = "Fight!";
			deltaWaitTime += deltaTime;
		}
		// 全オブジェクトの更新.
		ObjectManager::Update(deltaTime);
		ObjectManager::Collition();

		EffectManager::Update(deltaTime);
	}


	for (int i = 0; i < PlayerNum; i++)
	{
		if (player[i]->GetHP() <= 0)
		{
			CheckWinner();
			WaitTimer(WaitTime);
			ObjectManager::ReleseAllObj();
			return new EndScene(1);
			break;
		}

	}
	if (CheckHitKey(KEY_INPUT_F8))
	{
		ObjectManager::ReleseAllObj();
		return new EndScene(1);
	}
	return this;
}

void PlayScene::Draw()
{
	DrawExtendGraph(0, 0, ScreenSizeX, ScreenSizeY, imgHandle, false);
	if (deltaWaitTime < WaitingTimeBeforStart + StringDrawTime)
	{
		int strWidth = GetDrawStringWidthToHandle(str.c_str(), strlen(str.c_str()), fontHandle);
		DrawStringToHandle(ScreenSizeX / 2 - strWidth / 2, ScreenSizeY / 2, str.c_str(), Red, fontHandle);

	}
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
			winnerNum = i;
			break;
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
