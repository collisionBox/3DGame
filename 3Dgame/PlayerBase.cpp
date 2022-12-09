#include "PlayerBase.h"
//-----------------------------------------------------------------------------
// @brief  インスタンスの取得.
//-----------------------------------------------------------------------------
PlayerBase& PlayerBase::GetInstance()
{
	static PlayerBase PlayerBase;
	return PlayerBase;
}
//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
PlayerBase::PlayerBase()
	:modelHandle(-1)
	,hitRadius(5.0f)
{
	//3Dモデルの読み込み
	modelHandle = MV1LoadModel("data/player/recon");
	copyModelHandle = MV1DuplicateModel(modelHandle);
	if (modelHandle == -1)
	{
		printfDx("モデルハンドルの取得に失敗");
	}
	pos = VGet(0, 0, 0);
	velocity = VGet(0, 0, 0);
	dir = VGet(0, 0, 1);
}
//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------

PlayerBase::~PlayerBase()
{
	//モデルのアンロード
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

