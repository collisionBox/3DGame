//-----------------------------------------------------------------------------
// @brief  メイン処理.
//-----------------------------------------------------------------------------
#pragma warning(disable:4996)
#include "foundation.h"
#include <vector>

#include "Director.h"

#include "PlayerBody.h"
#include "EnemyBody.h"

#include "Map1.h"

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
	Director::Initalize();

	// カメラ生成.
	/*MainCamera* mainCam = new MainCamera(40, -90);
	ObjectManager::Entry(mainCam);*/
	MainCamera* mainCam = new MainCamera;

	// プレイヤー生成.
	int padInput = DX_INPUT_PAD1;
	PlayerBody* player = new PlayerBody(VGet(-742.0f+600, 0.0f, -30.0f), VGet(1.0f, 0.0f, 0.0f) ,padInput, ObjectTag::Player, "data/player1/");
	ObjectManager::Entry(player);

	int padInput2 = DX_INPUT_PAD2;
	PlayerBody* player2 = new PlayerBody(VGet(742.0f, 0.0f, -355.0f), VGet(-1.0f, 0.0f, 1.0f), padInput2, ObjectTag::Player2, "data/player2/");
	ObjectManager::Entry(player2);

	EnemyBody* enemy = new EnemyBody(VGet(742.0f, 0.0f, 355.0f), VGet(0.0f, 0.0f, -1.0f), "data/enemy/");
	ObjectManager::Entry(enemy);
	
	Map1* map = new Map1;
	ObjectManager::Entry(map);
	
	// UI生成.
	UI* ui = new UI();

	//時間計測.
	int nowTime = GetNowCount();
	int prevTime = nowTime;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//フレーム時間計測.
		nowTime = GetNowCount();
		float deltaTime = (nowTime - prevTime) / 1000.0f;
		
		// 全オブジェクトの更新.
		ObjectManager::Update(1.0f/60.0f);
		ObjectManager::Collition();
		Director::Update(deltaTime);

		//画面の初期化.
		ClearDrawScreen();

		// 全オブジェクトの描画.
		DrawGrid(3000, 100);
		ObjectManager::Draw();
		Director::Draw();

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
