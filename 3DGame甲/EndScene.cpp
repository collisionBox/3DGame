#include "EndScene.h"
#include "SystemConstant.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include "StartScene.h"
EndScene::EndScene(int winnerNum)
{
	fontHandle = CreateFontToHandle(NULL, fontSize, fontThick);
	alpha = 0;
	this->winnerNum = winnerNum;
	timer = 0.0f;
}

EndScene::~EndScene()
{
	DeleteFontToHandle(fontHandle);
}

SceneBase* EndScene::Update(float deltaTime)
{
	if (CheckHitKeyAll())
	{
		return new PlayScene(1);
	}
	timer += deltaTime;
	if (timer >= TransitionWaitingTime)
	{
		return new StartScene;
	}
	return this;
}

void EndScene::Draw()
{
	if (winnerNum == -1)
	{
		int strWidth = GetDrawStringWidthToHandle("Draw", strlen("Draw"), fontHandle);
		DrawFormatStringToHandle(ScreenSizeX / 2 - strWidth / 2, ScreenSizeY / 2, Green, fontHandle, "Draw");

	}
	else
	{
		int strWidth = GetDrawStringWidthToHandle("Winner Player ", strlen("Winner Player "), fontHandle);
		DrawFormatStringToHandle(ScreenSizeX / 2 - strWidth / 2, ScreenSizeY / 2, Green, fontHandle, "Winner Player%d!", winnerNum);

	}
	alpha += addition;
	if (alpha > 255)
	{
		addition *= -1;
	}
	if (alpha < 0)
	{
		addition *= -1;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	int strLne = strlen(Str.c_str());
	int strWidth = GetDrawStringWidth(Str.c_str(), strLne);
	DrawFormatString(ScreenSizeX / 2 - strWidth / 2, ScreenSizeY * 2 / 3, Green, Str.c_str());
	strLne = strlen(Str2.c_str());
	strWidth = GetDrawStringWidth(Str2.c_str(), strLne);
	DrawFormatString(ScreenSizeX / 2 - strWidth / 2, ScreenSizeY * 2 / 3 + str2Pos, Green, Str2.c_str());
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
}
