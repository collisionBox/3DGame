#include "PlayerBase.h"
//-----------------------------------------------------------------------------
// @brief  �C���X�^���X�̎擾.
//-----------------------------------------------------------------------------
PlayerBase& PlayerBase::GetInstance()
{
	static PlayerBase PlayerBase;
	return PlayerBase;
}
//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
PlayerBase::PlayerBase()
	:modelHandle(-1)
	,hitRadius(5.0f)
{
	//3D���f���̓ǂݍ���
	modelHandle = MV1LoadModel("data/player/recon");
	copyModelHandle = MV1DuplicateModel(modelHandle);
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

PlayerBase::~PlayerBase()
{
	//���f���̃A�����[�h
	MV1DeleteModel(modelHandle);
	MV1DeleteModel(copyModelHandle);
}

void PlayerBase::Update()
{
}

void PlayerBase::Draw()
{

	MV1DrawModel(modelHandle);
}

