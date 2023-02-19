//-----------------------------------------------------------------------------
// @brief  メイン処理.
//-----------------------------------------------------------------------------
#pragma warning(disable:4996)
#include "foundation.h"
#include <vector>

#include "Director.h"

#include "PlayerBody.h"
#include "EnemyBody.h"

#include "SceneHedder.h"
#include "MapManager.h"

#include "UI.h"
#include "Camera.h"
#include "DebugDraw.h"


//-----------------------------------------------------------------------------
// @brief  メイン関数.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ＤＸライブラリ初期化処理
	SetUseDirect3DVersion(DX_DIRECT3D_11);// 使用するDirectXバージョンを指定.
	ChangeWindowMode(TRUE);// ウィンドウモードの変更.

	// 画面モードセット.
	int screenMagni = 120;// 画面比率にかける倍率.
	SetGraphMode(16 * screenMagni, 9 * screenMagni, 16);
	SetBackgroundColor(70,70, 70);
	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	// ライトを設定.
	SetLightDirection(VGet(0.0f, -1.0f, 0.0f));

	// マネージャー生成.
	AssetManager::Initalize();
	ObjectManager::Initialize();

	SCENEINSTANCE.SetScene(new PlayScene);
	
	// UI生成.
	UI* ui = new UI();
	
	//時間計測.
	LONGLONG nowTime = GetNowHiPerformanceCount();
	LONGLONG prevTime = nowTime;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//フレーム時間計測.
		nowTime = GetNowHiPerformanceCount();
		float deltaTime = (nowTime - prevTime) / 1000000.0f;



		//画面の初期化.
		ClearDrawScreen();
		SCENEINSTANCE.Update(deltaTime);
		SCENEINSTANCE.Draw();
	
		DrawGrid(3000, 100);
		if (CheckHitKey(KEY_INPUT_TAB))
		{
			SCENEINSTANCE.SetScene(new OverScene);
		}
		

		ui->Draw(deltaTime);
		//裏画面の内容を表画面に反映させる.
		ScreenFlip();
		prevTime = nowTime;
	}

	delete ui;
	// オブジェクトの削除.
	ObjectManager::ReleseAllObj();
	ObjectManager::Finalize();

	// アセットの削除.
	AssetManager::DeleteAllAsset();
	AssetManager::Finalize();

	DxLib_End();

	return 0;
}
