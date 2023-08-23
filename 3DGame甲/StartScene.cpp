#include "StartScene.h"
#include "SystemConstant.h"
#include "SceneManager.h"
#include "PlayScene.h"
#include <cmath>
#include "Director.h"
StartScene::StartScene()
{
	singleMode = true;
	alpha = 0.0f;
}
SceneBase* StartScene::Update(float deltaTime)
{
	GetJoypadXInputState(DX_INPUT_PAD1, &input);
	シングルマルチ切り替え作成中
		ディレクターにて管理
	if (input.Buttons[XINPUT_BUTTON_DPAD_UP]|| input.Buttons[XINPUT_BUTTON_DPAD_DOWN])
	{

	}
	if (input.Buttons[XINPUT_BUTTON_START])
	{
		return new PlayScene(1);
	} 
	return this;
}

void StartScene::Draw()
{
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
	DrawFormatString(ScreenSizeX / 2 - StrWidth / 2, ScreenSizeY * 2 / 3, Green, Str.c_str());
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

}
