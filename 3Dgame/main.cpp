//-----------------------------------------------------------------------------
// @brief  ���C������.
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

	//���s0.1�`1000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(10.0f, 3000.0f);

	//(0,10,-20)�̎��_����(0,10,0)�̃^�[�Q�b�g������p�x�ɃJ������ݒu
	SetCameraPositionAndTarget_UpVecY(VGet(0, 80, -200), VGet(0.0f, 80.0f, 0.0f));

	//��ʃ��[�h�̃Z�b�g.

	//�}�l�[�W���[����.
	AssetManager::Initalize();
	ObjectManager::Initialize();

	//�J��������.
	MainCamera* mainCam = new MainCamera(500, -500);
	ObjectManager::Entry(mainCam);

	//�v���C���[����.
	PlayerBody* player = new PlayerBody();
	ObjectManager::Entry(player);

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

		//��ʂ̏�����.
		ClearDrawScreen();

		// �S�I�u�W�F�N�g�̕`��.
		DrawGrid(3000, 30);
		ObjectManager::Draw();

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
