//-----------------------------------------------------------
// @brief 背景クラス
//-----------------------------------------------------------
#pragma once

#include <DxLib.h>
#include "GameObject.h"

namespace My3dApp
{
	class BackGround : public My3dApp::GameObject
	{
	public:
		BackGround();                          // 背景クラスコンストラクタ
		BackGround(VECTOR pos);                // 位置指定
		~BackGround();                         // デストラクタ
		void ModelLoad();                      // モデル読み込み
		void Update(float deltaTime)override;  // 背景更新処理
		void Draw() override;                  // 背景描画
	};
}// namespace My3dApp