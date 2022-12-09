#include "Block.h"
#include "AssetManager.h"

namespace My3dApp
{
	//-----------------------------------------------------------------------
	// @brief Blockクラスコンストラクタ。モデルを読み込む
	//-----------------------------------------------------------------------
	Block::Block()
		: GameObject(My3dApp::ObjectTag::BackGround)
	{
		ModelLoad();
	}
	//-----------------------------------------------------------------------
	// @brief Blockクラスコンストラクタ。モデルを読み込む
	// @param[in] pos ブロックのワールド座標位置
	//-----------------------------------------------------------------------
	Block::Block(VECTOR pos)
		: GameObject(My3dApp::ObjectTag::BackGround, pos)
	{
		ModelLoad();
	}
	//-----------------------------------------------------------------------
	// @brief Blockクラス　デストラクタ
	//-----------------------------------------------------------------------
	Block::~Block()
	{
		AssetManager::ReleaseMesh(mModelHandle);
	}

	//-----------------------------------------------------------------------
	// @brief モデルを読み込み＆背景当たり判定情報構築
	//-----------------------------------------------------------------------
	void Block::ModelLoad()
	{
		// モデル読み込み後、当たり判定情報構築
		mModelHandle = AssetManager::GetMesh("data/model/block/block.mv1");
		mCollisionModel = mModelHandle;		
		MV1SetPosition(mModelHandle, mPos);
		CollisionUpdate();
	}

	//-----------------------------------------------------------------------
	// @brief ブロックモデルの更新処理。何も行わない。
	//-----------------------------------------------------------------------
	void Block::Update(float deltaTime)
	{
	}

	//-----------------------------------------------------------------------
	// @brief ブロックの描画
	//-----------------------------------------------------------------------
	void Block::Draw()
	{
		MV1SetPosition(mModelHandle, mPos);
		MV1DrawModel(mModelHandle);
	}

}