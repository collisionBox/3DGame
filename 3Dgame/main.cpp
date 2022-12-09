//-----------------------------------------------------------------------------
// @brief  メイン処理.
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include <vector>

#include "ObjectBase.h"
#include "ObjectManager.h"
#include "AssetManager.h"
#include "PlayerBody.h"
#include "Camera.h"

//-----------------------------------------------------------------------------
// @brief  メイン関数.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	//画面モードのセット.
	SetGraphMode(16*70, 9*70, 16);
	ChangeWindowMode(TRUE);//ウィンドウモードに設定
	//マネージャー生成.
	AssetManager::Initalize();
	ObjectManager::Initialize();


	//カメラ生成.
	Camera* camera = new Camera();

	//プレイヤー生成.
	PlayerBody* player = new PlayerBody();
	ObjectManager::Entry(player);

	//時間計測.
	int nowTime = GetNowCount();
	int prevTime = nowTime;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//フレーム時間計測.
		nowTime = GetNowCount();
		float deltaTime = (nowTime - prevTime) / 1000.0f;

		//プレイヤー制御.
		player->Update(deltaTime);

		//カメラ制御.
		camera->Update(deltaTime);

		//画面の初期化.
		ClearDrawScreen();

		ObjectManager::Draw();
		//裏画面の内容を表画面に反映させる.
		ScreenFlip();

		prevTime = nowTime;
	}

	ObjectManager::ReleseAllObj();
	ObjectManager::Finalize();

	AssetManager::DeleteAllAsset();
	AssetManager::Finalize();

	DxLib_End();

	return 0;
}
