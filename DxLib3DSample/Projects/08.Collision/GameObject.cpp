#include "GameObject.h"
#include "AssetManager.h"

namespace My3dApp
{
	//--------------------------------------------------------------------
	// @brief     ゲームオブジェクトコンストラクタ.
	// @param[in] tag オブジェクト種類
	//--------------------------------------------------------------------
	GameObject::GameObject(ObjectTag tag)
		: mTag(tag)
		, mPos()
		, mModelHandle(-1)
		, mVisible(true)
		, mAlive(true)
		, mCollisionType()
		, mCollisionLine()
		, mCollisionSphere()
		, mCollisionCapsule()
		, mCollisionModel(-1)
	{
	}

	//---------------------------------------------------------------------
	// @brief     ゲームオブジェクトコンストラクタ 位置セット.
	// @param[in] tag オブジェクト種類
	// @param[in] pos オブジェクト位置
	//-----------------------b---------------------------------------------
	GameObject::GameObject(ObjectTag tag, VECTOR pos)
		: mTag(tag)
		, mPos()
		, mModelHandle(-1)
		, mVisible(true)
		, mAlive(true)
		, mCollisionType()
		, mCollisionLine()
		, mCollisionSphere()
		, mCollisionCapsule()
		, mCollisionModel()
	{
		mPos = pos;
	}

	//--------------------------------------------------------------------
	// @brief ゲームオブジェクトデストラクタ.
	//--------------------------------------------------------------------
	GameObject::~GameObject()
	{
		if (mModelHandle != -1)
		{
			AssetManager::ReleaseMesh(mModelHandle);
			mModelHandle = -1;
		}
	}
	//--------------------------------------------------------------------
	// @brief 描画.
	//--------------------------------------------------------------------
	void GameObject::Draw()
	{
	}

	//--------------------------------------------------------------------
	// @brief コライダーの描画.
	//--------------------------------------------------------------------
	void GameObject::DrawCollider()
	{
		// 全コライダー種の描画
		DrawLine3D(mCollisionLine.mWorldStart, mCollisionLine.mWorldEnd, GetColor(255, 255, FALSE));
		DrawSphere3D(mCollisionSphere.mWorldCenter, mCollisionSphere.mRadius, 10, GetColor(0, 255, 255), GetColor(0, 0, 0), FALSE);
		DrawCapsule3D(mCollisionCapsule.mWorldStart, mCollisionCapsule.mWorldEnd, mCollisionCapsule.mRadius, 8, GetColor(255, 0, 255), GetColor(0, 0, 0), FALSE);

		// コリジョンモデルが存在する場合は半透明描画
		if (mCollisionModel != -1)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
			MV1DrawModel(mCollisionModel);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND,255);
		}
	}
	//---------------------------------------------------------------------------------
	// @brief  当たり判定更新処理
	// @detail GameObjectが移動したときには当たり判定位置もそれに合わせて更新する必要がある。
	// 当たり判定がモデル(メッシュ)の場合、ポリゴンごとの当たり判定情報を再構築するため、
	// 呼び出し回数を少なくする工夫が必要。その他の球・線分・カプセルは問題なく、毎フレーム
	// 呼び出しても問題ない。
	//---------------------------------------------------------------------------------
	void GameObject::CollisionUpdate()
	{
		mCollisionSphere.Move(mPos);
		mCollisionLine.Move(mPos);
		mCollisionCapsule.Move(mPos);

		// モデルの当たり判定情報を再構築
		if (mCollisionModel != -1)
		{
			MV1SetPosition(mCollisionModel, mPos);
			MV1SetupCollInfo(mCollisionModel);
		}
	}
}