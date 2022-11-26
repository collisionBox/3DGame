#include "Player.h"
//-----------------------------------------------------------------------------
// @brief  インスタンスの取得.
//-----------------------------------------------------------------------------
Player& Player::GetInstance()
{
	static Player Player;
	return Player;
}
//-----------------------------------------------------------------------------
// @brief  コンストラクタ.
//-----------------------------------------------------------------------------
Player::Player()
	:modelHandle(-1)
	,hitRadius(5.0f)
{
	//3Dモデルの読み込み
	modelHandle = MV1LoadModel("data/player/hackadoll.pmx");
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

Player::~Player()
{
	//モデルのアンロード
	MV1DeleteModel(modelHandle);
}

void Player::Update()
{
}

void Player::Draw()
{
	MV1DrawModel(modelHandle);
}

