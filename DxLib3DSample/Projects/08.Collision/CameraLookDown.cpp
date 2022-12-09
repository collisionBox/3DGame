#include "CameraLookDown.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "ObjectTag.h"
#include "Player.h"

namespace My3dApp
{
	// カメラのばね定数
	const float camSpringStrength = 2.0f;

	//-----------------------------------------------------------------------
	// @brief CameraLookDownクラスコンストラクタ。見下ろしカメラ
	// @param[in] camHeight カメラとプレイヤーとの相対座標高さ
	// @param[in] camZpos   カメラとプレイヤーとの相対Z座標
	//-----------------------------------------------------------------------
	CameraLookDown::CameraLookDown(float camHeight, float camZpos)
		: GameObject(ObjectTag::Camera)
		, mPos()
		, mLookPos()
		, mCamOffset()
		, mAimCamPos()
		, mAimLookPos()
	{
		mCamOffset.x = 0;
		mCamOffset.y = camHeight;
		mCamOffset.z = camZpos;
	}

	//-----------------------------------------------------------------------
	// @brief 見下ろしカメラUpdate処理
	// @param[in] deltaTime １フレームの経過時間
	//-----------------------------------------------------------------------
	void CameraLookDown::Update(float deltaTime)
	{
		// カメラの注視目標点と、カメラの位置目標点を計算
		GameObject* player = GameObjectManager::GetFirstGameObject(ObjectTag::Player);
		if (player)
		{
			mAimLookPos = player->GetPos();
			mAimCamPos = mAimLookPos + mCamOffset;

			// カメラ位置から目標点に向かうベクトルを計算
			VECTOR lookMoveDir = mAimLookPos - mLookPos;
			VECTOR posMoveDir = mAimCamPos - mPos;

			// 注視点と、カメラ位置を徐々に目標地点に近づける
			mLookPos += lookMoveDir * camSpringStrength * deltaTime;
			mPos += posMoveDir * camSpringStrength * deltaTime;

			SetCameraPositionAndTarget_UpVecY(mPos, mLookPos);
		}
	}

}// namespace My3dApp