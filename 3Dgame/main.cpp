//-----------------------------------------------------------------------------
// @brief  ���C������.
//-----------------------------------------------------------------------------
#pragma warning(disable:4996)
#include "DxLib.h"
#include <vector>

#include "ObjectBase.h"
#include "ObjectManager.h"
#include "AssetManager.h"
#include "Director.h"
#include "UI.h"
#include "PlayerBody.h"
#include "Camera.h"
#include "DebugDraw.h"


//-----------------------------------------------------------------------------
// @brief  ���C���֐�.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �c�w���C�u��������������
	SetUseDirect3DVersion(DX_DIRECT3D_11);
	ChangeWindowMode(TRUE);
	// ��ʃ��[�h�Z�b�g.
	SetGraphMode(16 * 70, 9 * 70, 16);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	//�}�l�[�W���[����.
	AssetManager::Initalize();
	ObjectManager::Initialize();
	Director::Initalize();

	//�J��������.
	MainCamera* mainCam = new MainCamera(40, -90);
	ObjectManager::Entry(mainCam);

	//�v���C���[����.
	PlayerBody* player = new PlayerBody();
	ObjectManager::Entry(player);

	// UI����.
	UI* ui = new UI();

	//���Ԍv��.
	int nowTime = GetNowCount();
	int prevTime = nowTime;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�t���[�����Ԍv��.
		nowTime = GetNowCount();
		float deltaTime = (nowTime - prevTime) / 1000.0f;

		// �S�I�u�W�F�N�g�̍X�V.
		ObjectManager::Update(deltaTime);
		//ObjectManager::Collition();
		Director::Update(deltaTime);

		//��ʂ̏�����.
		ClearDrawScreen();

		// �S�I�u�W�F�N�g�̕`��.
		DrawGrid(3000, 100);
		ObjectManager::Draw();
		Director::Draw();

		ui->Draw(deltaTime);

		//����ʂ̓��e��\��ʂɔ��f������.
		ScreenFlip();
		
		prevTime = nowTime;
	}

	// �I�u�W�F�N�g�̍폜.
	ObjectManager::ReleseAllObj();
	ObjectManager::Finalize();

	// �A�Z�b�g�̍폜.
	AssetManager::DeleteAllAsset();
	AssetManager::Finalize();

	DxLib_End();

	return 0;
}
