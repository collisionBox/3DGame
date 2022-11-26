//-----------------------------------------------------------------------------
// @brief  メイン処理.
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Camera.h"
#include "Player.h"
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

	//カメラ生成.
	Camera* camera = new Camera();

	//プレイヤー生成.
	Player* player = new Player();

	//時間計測.
	int nowTime = GetNowCount();
	int prevTime = nowTime;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//フレーム時間計測.
		nowTime = GetNowCount();
		float deltaTime = (nowTime - prevTime) / 1000.0f;

		//プレイヤー制御.
		player->Update();

		//カメラ制御.
		camera->Update(deltaTime);

		//画面の初期化.
		ClearDrawScreen();
		//地面グリッドを描画する（のちにゲームオブジェクトにしよう）
		{
			const float gridAllSize = 1000.0f;
			const int divideNum = 10;
			const float gridSpace = gridAllSize / divideNum;

			VECTOR p1;
			VECTOR p2;
			for (int ix = 0; ix < divideNum + 1; ix++)
			{
				p1 = VGet(ix * gridSpace - gridAllSize * 0.5f, 0.0f, -gridAllSize * 0.5f);
				p2 = VGet(ix * gridSpace - gridAllSize * 0.5f, 0.0f, gridAllSize * 0.5f);

				DrawLine3D(p1, p2, GetColor(0, 255, 0));
			}

			for (int iy = 0; iy < divideNum + 1; iy++)
			{
				p1 = VGet(-gridAllSize * 0.5f, 0.0f, iy * gridSpace - gridAllSize * 0.5f);
				p2 = VGet(+gridAllSize * 0.5f, 0.0f, iy * gridSpace - gridAllSize * 0.5f);

				DrawLine3D(p1, p2, GetColor(0, 255, 0));
			}
		}//グリッド描画終わ
		//プレイヤー描画.
		player->Draw();

		//裏画面の内容を表画面に反映させる.
		ScreenFlip();

		prevTime = nowTime;
	}



	return 0;
}
