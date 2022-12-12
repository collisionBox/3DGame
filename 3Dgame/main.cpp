//-----------------------------------------------------------------------------
// @brief  メイン処理.
//-----------------------------------------------------------------------------
#pragma warning(disable:4996)
#include "DxLib.h"
#include <vector>

#include "ObjectBase.h"
#include "ObjectManager.h"
#include "AssetManager.h"
#include "PlayerBody.h"
#include "Camera.h"
#include "DebugDraw.h"


//-----------------------------------------------------------------------------
// @brief  メイン関数.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// ＤＸライブラリ初期化処理
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	ChangeWindowMode(TRUE);
	// 画面モードセット.
	SetGraphMode(16 * 70, 9 * 70, 16);

	if (DxLib_Init() == -1)		// ＤＸライブラリ初期化処理
	{
		return -1;			// エラーが起きたら直ちに終了
	}

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(10.0f, 3000.0f);

	//(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(VGet(0, 80, -200), VGet(0.0f, 80.0f, 0.0f));

	//画面モードのセット.

	//マネージャー生成.
	AssetManager::Initalize();
	ObjectManager::Initialize();

	//カメラ生成.
	MainCamera* mainCam = new MainCamera(500, -500);
	ObjectManager::Entry(mainCam);

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

		// 全オブジェクトの更新.
		ObjectManager::Update(deltaTime);
		//ObjectManager::Collition();

		//画面の初期化.
		ClearDrawScreen();

		// 全オブジェクトの描画.
		DrawGrid(3000, 30);
		ObjectManager::Draw();

		//裏画面の内容を表画面に反映させる.
		ScreenFlip();

		prevTime = nowTime;
	}

	// オブジェクトの削除.
	ObjectManager::ReleseAllObj();
	ObjectManager::Finalize();

	// アセットの削除.
	AssetManager::DeleteAllAsset();
	AssetManager::Finalize();

	DxLib_End();

	return 0;
}
