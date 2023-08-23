#include "PlayScene.h"
#include "ObjectManager.h"
#include "EffectManager.h"
#include "EndScene.h"
#include "Director.h"

PlayScene::PlayScene(int mapNum)
{
	imgHandle = LoadGraph("data/floor.jpg");

	ObjectManager::ReleseAllObj();

	// �J��������.
	MainCamera* mainCam = new MainCamera;

	// �v���C���[����.
	int padInput = DX_INPUT_PAD1;
	player[0] = new PlayerBody(Player1InitPos, Player1InitDir, padInput, ObjectTag::Player1, "data/player1/");
	ObjectManager::Entry(player[0]);

	/*int padInput2 = DX_INPUT_PAD2;
	player[1] = new PlayerBody(Player2InitPos, Player2InitDir, padInput2, ObjectTag::Player2, "data/player2/");
	ObjectManager::Entry(player[1]);*/

	enemy = new EnemyBody(Player2InitPos, Player2InitDir);
	ObjectManager::Entry(enemy);

	MapManager* map = new MapManager(mapNum);
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
		// �S�I�u�W�F�N�g�̍X�V.
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
	DrawExtendGraph(0, 0, ScreenSizeX, ScreenSizeY, imgHandle, false);
	if (deltaWaitTime < WaitingTimeBeforStart + StringDrawTime)
	{
		int strWidth = GetDrawStringWidthToHandle(str.c_str(), strlen(str.c_str()), fontHandle);
		DrawStringToHandle(ScreenSizeX / 2 - strWidth / 2, ScreenSizeY / 2, str.c_str(), Red, fontHandle);

	}
	// �S�I�u�W�F�N�g�̕`��.
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
