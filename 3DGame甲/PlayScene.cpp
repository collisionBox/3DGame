#include "PlayScene.h"
#include "ObjectManager.h"
#include "EffectManager.h"
#include "EndScene.h"

PlayScene::PlayScene(int mapNum)
{
	ObjectManager::ReleseAllObj();

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

	fontHandle = CreateFontToHandle(NULL, fontSize, fontThick);
	str = "Redy";

}

PlayScene::~PlayScene()
{
}

SceneBase* PlayScene::Update(float deltaTime)
{
	if (deltaWaitTime < WaitingTimeBeforStart)
	{
		deltaWaitTime += deltaTime;
		str = "Redy";
	}
	else
	{
		if (deltaWaitTime < WaitingTimeBeforStart + StringDrawTime)
		{
			str = "Figth!";
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
			return new EndScene(winnerNum + 1);
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
	if (deltaWaitTime < WaitingTimeBeforStart + StringDrawTime)
	{
		int strWidth = GetDrawStringWidthToHandle(str.c_str(), strlen(str.c_str()), fontHandle);
		DrawStringToHandle(ScreenSizeX / 2 - strWidth / 2, ScreenSizeY / 2, str.c_str(), White, fontHandle);

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
