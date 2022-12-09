//-------------------------------------------------------------
// @brief 見下ろしカメラクラス
//-------------------------------------------------------------
#pragma once

#include <DxLib.h>
#include "math3D.h"
#include "GameObject.h"

namespace My3dApp
{
	class CameraLookDown : public GameObject
	{
	public:
		CameraLookDown(float camheight, float camzpos); // カメラの初期値
		~CameraLookDown() {};

		void Update(float deltaTime)override; 

	private:
		VECTOR mPos;               // カメラ位置
		VECTOR mLookPos;           // カメラの注目点
		VECTOR mCamOffset;         // プレイヤーからの相対位置

		VECTOR mAimCamPos;         // カメラ目標位置
		VECTOR mAimLookPos;        // カメラ注目点目標
	};

} //namespace My3dApp