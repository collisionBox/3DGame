//-----------------------------------------------------------------------------
// @brief  メイン処理.
//-----------------------------------------------------------------------------
#pragma warning(disable:4996)
#include <vector>
#include <DxLib.h>

#include "GameObject.h"
#include "GameObjectManager.h"
#include "AssetManager.h"
#include "Player.h"
#include "CameraLookDown.h"
#include "Block.h"
#include "BackGround.h"
#include "DebugDraw.h"

//void DrawGrid();

//-----------------------------------------------------------------------------
// @brief  メイン関数.
//-----------------------------------------------------------------------------
int WINAPI _stdcall WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) 
{
	// ＤＸライブラリ初期化処理
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	ChangeWindowMode(TRUE);
	// 画面モードのセット
	SetGraphMode(1280, 1024, 16);

	if (DxLib_Init() == -1)		
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// Ｚバッファを有効にする
	SetUseZBuffer3D(TRUE);

	// Ｚバッファへの書き込みを有効にする
	SetWriteZBuffer3D(TRUE);

	//奥行0.1～1000までをカメラの描画範囲とする
	SetCameraNearFar(10.0f, 3000.0f);

	//(0,10,-20)の視点から(0,10,0)のターゲットを見る角度にカメラを設置
	SetCameraPositionAndTarget_UpVecY(VGet(0, 80, -200), VGet(0.0f, 80.0f, 0.0f));

	// アセットマネージャ・ゲームオブジェクトマネージャの作成
	My3dApp::AssetManager::Initialize();
	My3dApp::GameObjectManager::Initialize();

	// プレイヤーを生成.
	My3dApp::Player* player = new My3dApp::Player;
	My3dApp::GameObjectManager::Entry(player);

	// カメラを生成
	My3dApp::CameraLookDown* camera = new My3dApp::CameraLookDown(500, -500);
	My3dApp::GameObjectManager::Entry(camera);

	// ブロックを生成
	My3dApp::GameObjectManager::Entry(new My3dApp::Block(VGet(100, 0,   0)));
	My3dApp::GameObjectManager::Entry(new My3dApp::Block(VGet(200, 0, 100)));
	My3dApp::GameObjectManager::Entry(new My3dApp::Block(VGet(400, 0, 300)));
	My3dApp::GameObjectManager::Entry(new My3dApp::Block(VGet(100, 0, 100)));
	My3dApp::GameObjectManager::Entry(new My3dApp::Block(VGet(500, 0, 200)));

	// マップを生成
	My3dApp::GameObjectManager::Entry(new My3dApp::BackGround(VGet(0,-225,0)));

	// 時間計測
	int nowTime  = GetNowCount();
	int prevTime = nowTime;

	// エスケープキーが押されるかウインドウが閉じられるまでループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		// フレーム時間を算出
		nowTime = GetNowCount();
		float deltaTime = (nowTime - prevTime)/ 1000.0f;

		// すべてのゲームオブジェクトの更新
		My3dApp::GameObjectManager::Update(deltaTime);
		My3dApp::GameObjectManager::Collision();

		// 画面を初期化する
		ClearDrawScreen();

		My3dApp::DrawGrid(3000, 30);

		//すべてのゲームオブジェクトの描画
		My3dApp::GameObjectManager::Draw();
		
		// 裏画面の内容を表画面に反映させる
		ScreenFlip();

		prevTime = nowTime;
	}

	// ゲームオブジェクトの削除
	My3dApp::GameObjectManager::ReleaseAllObj();
	My3dApp::GameObjectManager::Finalize();

	// ゲームアセットの削除
	My3dApp::AssetManager::ReleaseAllAsset();
	My3dApp::AssetManager::Finalize();

	// ＤＸライブラリの後始末
	DxLib_End();

	// ソフトの終了
	return 0;
}
