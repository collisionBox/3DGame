//-----------------------------------------------------------------------------
// @brief  ���C������.
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
// @brief  ���C���֐�.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �c�w���C�u��������������
	SetUseDirect3DVersion(DX_DIRECT3D_11);// �g�p����DirectX�o�[�W�������w��.
	ChangeWindowMode(TRUE);// �E�B���h�E���[�h�̕ύX.

	// ��ʃ��[�h�Z�b�g.
	int screenMagni = 120;// ��ʔ䗦�ɂ�����{��.
	SetGraphMode(16 * screenMagni, 9 * screenMagni, 16);
	SetBackgroundColor(70,70, 70);
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	// ���C�g��ݒ�.
	SetLightDirection(VGet(0.0f, -1.0f, 0.0f));

	// �}�l�[�W���[����.
	AssetManager::Initalize();
	ObjectManager::Initialize();

	SCENEINSTANCE.SetScene(new PlayScene);
	
	// UI����.
	UI* ui = new UI();
	
	//���Ԍv��.
	LONGLONG nowTime = GetNowHiPerformanceCount();
	LONGLONG prevTime = nowTime;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�t���[�����Ԍv��.
		nowTime = GetNowHiPerformanceCount();
		float deltaTime = (nowTime - prevTime) / 1000000.0f;



		//��ʂ̏�����.
		ClearDrawScreen();
		SCENEINSTANCE.Update(deltaTime);
		SCENEINSTANCE.Draw();
	
		DrawGrid(3000, 100);
		if (CheckHitKey(KEY_INPUT_TAB))
		{
			SCENEINSTANCE.SetScene(new OverScene);
		}
		

		ui->Draw(deltaTime);
		//����ʂ̓��e��\��ʂɔ��f������.
		ScreenFlip();
		prevTime = nowTime;
	}

	delete ui;
	// �I�u�W�F�N�g�̍폜.
	ObjectManager::ReleseAllObj();
	ObjectManager::Finalize();

	// �A�Z�b�g�̍폜.
	AssetManager::DeleteAllAsset();
	AssetManager::Finalize();

	DxLib_End();

	return 0;
}
