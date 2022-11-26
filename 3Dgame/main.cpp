//-----------------------------------------------------------------------------
// @brief  ���C������.
//-----------------------------------------------------------------------------
#include "DxLib.h"
#include "Camera.h"
#include "Player.h"
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

	//�J��������.
	Camera* camera = new Camera();

	//�v���C���[����.
	Player* player = new Player();

	//���Ԍv��.
	int nowTime = GetNowCount();
	int prevTime = nowTime;

	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		//�t���[�����Ԍv��.
		nowTime = GetNowCount();
		float deltaTime = (nowTime - prevTime) / 1000.0f;

		//�v���C���[����.
		player->Update();

		//�J��������.
		camera->Update(deltaTime);

		//��ʂ̏�����.
		ClearDrawScreen();
		//�n�ʃO���b�h��`�悷��i�̂��ɃQ�[���I�u�W�F�N�g�ɂ��悤�j
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
		}//�O���b�h�`��I��
		//�v���C���[�`��.
		player->Draw();

		//����ʂ̓��e��\��ʂɔ��f������.
		ScreenFlip();

		prevTime = nowTime;
	}



	return 0;
}
