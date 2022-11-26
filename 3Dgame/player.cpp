#include "Player.h"
//-----------------------------------------------------------------------------
// @brief  �C���X�^���X�̎擾.
//-----------------------------------------------------------------------------
Player& Player::GetInstance()
{
	static Player Player;
	return Player;
}
//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
Player::Player()
	:modelHandle(-1)
	,hitRadius(5.0f)
{
	//3D���f���̓ǂݍ���
	modelHandle = MV1LoadModel("data/player/hackadoll.pmx");
	if (modelHandle == -1)
	{
		printfDx("���f���n���h���̎擾�Ɏ��s");
	}
	pos = VGet(0, 0, 0);
	velocity = VGet(0, 0, 0);
	dir = VGet(0, 0, 1);
}
//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------

Player::~Player()
{
	//���f���̃A�����[�h
	MV1DeleteModel(modelHandle);
}

void Player::Update()
{
}

void Player::Draw()
{
	MV1DrawModel(modelHandle);
}

