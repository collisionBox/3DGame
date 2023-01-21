//-----------------------------------------------------------------------------
// @brief  ���C������.
//-----------------------------------------------------------------------------
#pragma warning(disable:4996)
#include "foundation.h"
#include <vector>

#include "Director.h"

#include "Player.h"
#include "Player2.h"
#include "EnemyBody.h"

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

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �y�o�b�t�@��L���ɂ���
	SetUseZBuffer3D(TRUE);

	// �y�o�b�t�@�ւ̏������݂�L���ɂ���
	SetWriteZBuffer3D(TRUE);

	// ���C�g��ݒ� �f���[�g��DxLib_End()�ōs�Ȃ��邽�ߌ���s�K�v.
	int lightHandle = CreateDirLightHandle(VGet(-1.0f, 0.0f, 0.0f));

	// �}�l�[�W���[����.
	AssetManager::Initalize();
	ObjectManager::Initialize();
	Director::Initalize();

	// �J��������.
	/*MainCamera* mainCam = new MainCamera(40, -90);
	ObjectManager::Entry(mainCam);*/
	MainCamera* mainCam = new MainCamera;

	// �v���C���[����.
	int padInput = DX_INPUT_PAD1;
	PlayerBody* player = new PlayerBody(VGet(-742.0f, 0.0f, -355.0f), VGet(1.5f, 0.0f, 1.5f) ,padInput, ObjectTag::Player);
	ObjectManager::Entry(player);
	//ObjectManager::Entry(player1);

	int padInput2 = DX_INPUT_PAD2;
	//Player2* player2 = new Player2(VGet(742.0f, 0.0f, 355.0f), VGet(-1.5f, 0.0f, -1.5f), padInput2);
	//ObjectManager::Entry(player2);

	EnemyBody* enemy = new EnemyBody(VGet(742.0f, -10.0f, 355.0f), VGet(0.0f, 0.0f, -1.5f));
	ObjectManager::Entry(enemy);
	
	
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
		ObjectManager::Collition();
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
