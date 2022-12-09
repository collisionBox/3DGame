//-----------------------------------------------------------------------------
// @brief  プレイヤークラス.
//-----------------------------------------------------------------------------
#pragma once

#include <DxLib.h>
#include "GameObject.h"

namespace My3dApp
{
	class Player : public GameObject
	{
	public:
		Player();			 	                  // コンストラクタ.
		~Player();				                  // デストラクタ.
												  
		void Update(float deltaTime) override;    // 更新.
		void Draw() override;			          // 描画.
		void OnCollisonEnter(const GameObject* other) override; // 当たり判定

	private:
		void Input(float deltaTime);              // 入力移動処理
		void Rotate();                            // 回転処理
											      
		VECTOR  mDir;                             // 向き
		VECTOR  mAimDir;                          // 目標向き
		VECTOR  mVelocity;                        // 速度

		class   AnimationController* mAnimControl;// アニメーション管理用
		int     mAnimTypeId;                      // アニメーション種類ID
		bool    mRotateNow;                       // 回転中か
	};

}// namespace My3dApp