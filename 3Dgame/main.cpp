//-----------------------------------------------------------------------------
// @brief  ���C������.
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
	Director::Initalize();

	// �J��������.
	/*MainCamera* mainCam = new MainCamera(40, -90);
	ObjectManager::Entry(mainCam);*/
	MainCamera* mainCam = new MainCamera;

	// �v���C���[����.
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
		ObjectManager::Update(1.0f/60.0f);
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
