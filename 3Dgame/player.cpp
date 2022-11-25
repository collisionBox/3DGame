#include "player.h"
//-----------------------------------------------------------------------------
// @brief  インスタンスの取得.
//-----------------------------------------------------------------------------
player& player::GetInstance()
{
	static player player;
	return player;
}
//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
player::player()
	:modelHandle(-1)
	,hitRadius(5.0f)
{
	//3Dモデルの読み込み
	modelHandle = MV1LoadModel("");

	pos = VGet(0, 0, 0);
	velocity = VGet(0, 0, 0);
	dir = VGet(0, 0, 1);
}
//-----------------------------------------------------------------------------
// @brief  デストラクタ.
//-----------------------------------------------------------------------------

player::~player()
{
	//モデルのアンロード
	MV1DeleteModel(modelHandle);
}

void player::Update()
{
}

void player::Draw()
{

}

