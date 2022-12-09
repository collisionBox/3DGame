//-----------------------------------------------------------------------------
// @brief  ���C������.
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include <vector>

#include "ObjectBase.h"
#include "ObjectManager.h"
#include "AssetManager.h"
#include "PlayerBody.h"
#include "Camera.h"

//-----------------------------------------------------------------------------
// @brief  ���C���֐�.
//-----------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	//��ʃ��[�h�̃Z�b�g.
	SetGraphMode(16*70, 9*70, 16);
	ChangeWindowMode(TRUE);//�E�B���h�E���[�h�ɐݒ�
	//�}�l�[�W���[����.
	AssetManager::Initalize();
	ObjectManager::Initialize();


	//�J��������.
	Camera* camera = new Camera();

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

		//�v���C���[����.
		player->Update(deltaTime);

		//�J��������.
		camera->Update(deltaTime);

		//��ʂ̏�����.
		ClearDrawScreen();

		ObjectManager::Draw();
		//����ʂ̓��e��\��ʂɔ��f������.
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
