#include "player.h"
//-----------------------------------------------------------------------------
// @brief  �C���X�^���X�̎擾.
//-----------------------------------------------------------------------------
player& player::GetInstance()
{
	static player player;
	return player;
}
//-----------------------------------------------------------------------------
// @brief  �R���X�g���N�^.
//-----------------------------------------------------------------------------
player::player()
	:modelHandle(-1)
	,hitRadius(5.0f)
{
	//3D���f���̓ǂݍ���
	modelHandle = MV1LoadModel("");

	pos = VGet(0, 0, 0);
	velocity = VGet(0, 0, 0);
	dir = VGet(0, 0, 1);
}
//-----------------------------------------------------------------------------
// @brief  �f�X�g���N�^.
//-----------------------------------------------------------------------------

player::~player()
{
	//���f���̃A�����[�h
	MV1DeleteModel(modelHandle);
}

void player::Update()
{
}

void player::Draw()
{

}
