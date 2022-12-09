//--------------------------------------------------------------------------
// @brief ブロッククラス
// 
//--------------------------------------------------------------------------
#pragma once

#include <DxLib.h>
#include "GameObject.h"

namespace My3dApp
{
	class Block : public GameObject
	{
	public:
		Block();                               // Blockクラスコンストラクタ
		Block(VECTOR pos);                     // 位置付き初期化
		~Block();                              // デストラクタ
		void ModelLoad();                      // モデル読み込み
		void Update(float deltaTime) override; // 更新処理
		void Draw() override;                  // 描画処理

	};
} // namespace My3dApp