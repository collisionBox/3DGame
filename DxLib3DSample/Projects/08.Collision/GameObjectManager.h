//------------------------------------------------------------------------------
// @brief ゲームオブジェクトマネージャ
//------------------------------------------------------------------------------
#pragma once

#include <vector>
#include <unordered_map>
#include <DxLib.h>

#include "GameObject.h"
#include "ObjectTag.h"
#include "math3D.h"

namespace My3dApp
{
	class GameObjectManager final
	{
	public:
		static void Initialize();                                  // ゲームオブジェクトマネージャの初期化処理
		static void Entry(GameObject* newObj);                 // ゲームオブジェクト登録
		static void Release(GameObject* releaseObj);            // ゲームオブジェクト削除
		static void ReleaseAllObj();                           // 全オブジェクト削除

		static void Update(float deltaTime);                   // 全オブジェクトの更新処理
		static void Draw();                                    // 描画 

		static void Collision();                               // 当たり判定

		static GameObject* GetFirstGameObject(ObjectTag tag);  // オブジェクトタグ種の最初のGameObjectを返す

		static void Finalize();

	private:
		GameObjectManager();                                   // シングルトン
		~GameObjectManager();                                  // ゲームオブジェクトマネージャデストラクタ
		static GameObjectManager*                              mpInstance;      // マネージャの実体（アプリ内に唯一存在)
		std::vector<GameObject*>                               mPendingObjects; // 一時待機オブジェクト
		std::unordered_map<ObjectTag,std::vector<GameObject*>> mObjects;        // mObjects[タグ種類][オブジェクト個数]; 
	};

}// namespace My3dApp
