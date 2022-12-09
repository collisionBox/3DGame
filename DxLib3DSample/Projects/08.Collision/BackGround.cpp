#include "BackGround.h"
#include "ObjectTag.h"
#include "AssetManager.h"

namespace My3dApp
{
	//----------------------------------------------------------------------
	// @brief BackGroundクラスコンストラクタ。モデルを読み込む
	//----------------------------------------------------------------------
	My3dApp::BackGround::BackGround()
		: GameObject(My3dApp::ObjectTag::BackGround)
	{
		ModelLoad();
	}
	//----------------------------------------------------------------------
	// @brief BackGroundクラスコンストラクタ。モデルを読み込む
	// @param[in] pos 背景のワールド配置位置
	//----------------------------------------------------------------------
	BackGround::BackGround(VECTOR pos)
		: GameObject(My3dApp::ObjectTag::BackGround, pos)
	{
		ModelLoad();
	}

	//----------------------------------------------------------------------
	// @brief BackGroundクラスデストラクタ
	//----------------------------------------------------------------------
	BackGround::~BackGround()
	{
		AssetManager::ReleaseMesh(mModelHandle);
	}

	//----------------------------------------------------------------------
	// @brief 背景モデル読み込み
	//----------------------------------------------------------------------
	void BackGround::ModelLoad()
	{
		// 表示モデル読み込み＆スケーリング＆位置セット
		mModelHandle = AssetManager::GetMesh("data/model/map/maptest2.mv1");
		MV1SetScale(mModelHandle, VGet(1.0f, 1.0f, 1.0f));
		MV1SetPosition(mModelHandle, mPos);

		// 当たり判定モデル読み込み＆スケーリング＆当たり判定情報構築
		mCollisionModel = AssetManager::GetMesh("data/model/map/HitMesh2rot.mv1");
		MV1SetScale(mCollisionModel, VGet(1.0f, 1.0f, 1.0f));
		MV1SetOpacityRate(mCollisionModel, 0.3f);

		// 表示モデルと当たり判定モデルの位置を微調整
		MV1SetPosition(mCollisionModel, mPos + VGet(-45, 200, -35));

		MV1SetupCollInfo(mCollisionModel);

	}
	//----------------------------------------------------------------------
	// @brief 背景のアップデート処理。背景は動かないので何もしない.
	// @param[in] deltaTime １フレームの経過時間.
	//----------------------------------------------------------------------
	void BackGround::Update(float deltaTime)
	{
	}

	//----------------------------------------------------------------------
	// @brief 背景の描画処理.
	//----------------------------------------------------------------------
	void BackGround::Draw()
	{
		MV1DrawModel(mModelHandle);
		DrawCollider();
	}

}// namespace My3dApp