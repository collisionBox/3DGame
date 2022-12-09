//-----------------------------------------------------------
// @brief ゲームオブジェクト基底クラス
// ゲーム内に登場させるオブジェクトはこのクラスを派生させて作成する
//-----------------------------------------------------------
#pragma once 

#include <DxLib.h>
#include "ObjectTag.h"
#include "Collision.h"
#include "CollisionType.h"

namespace My3dApp
{
	class GameObject
	{
	public:

		GameObject(ObjectTag tag);                                             // ゲームオブジェクトコンストラクタ
		GameObject(ObjectTag tag, VECTOR pos);                                 // ゲームオブジェクトコンストラクタ
																	           
		virtual       ~GameObject();                                           // デストラクタ
																	           
		const         VECTOR& GetPos() const { return mPos; }                  // 位置取得 
		void          SetPos(const VECTOR set) { mPos = set; }                 // 位置セット
																	           
		bool          GetVisible() const { return mVisible; }                  // 可視状態の取得 
		void          SetVisible(bool visible) { mVisible = visible; }         // 可視状態のセット
																	           
		bool          GetAlive() const { return mAlive; }                      // ゲームオブジェクト生きているか 
		void          SetAlive(bool alive) { mAlive = alive; }                 // ゲームオブジェクト生死セット
																	           
		virtual void  Update(float deltaTime) = 0;                             // ゲームオブジェクト更新処理
		virtual void  Draw();                                                  // ゲームオブジェクト描画
		ObjectTag     GetTag()const { return mTag; }                           // ゲームオブジェクトの種類取得
																		       
		// 当たり判定関連												        
		virtual void  OnCollisonEnter(const GameObject* other) {}              // 他のオブジェクトとぶつかったときのリアクション（あれば）
		virtual void  Collision(GameObject* other) {};                         // このオブジェクトとの当たり判定

		CollisionType GetCollisionType() const   { return mCollisionType; }    // このオブジェクトが持っている当たり判定種を取得
		LineSegment   GetCollisionLine() const   { return mCollisionLine; }    // 当たり判定Lineを返却（持っていれば）
		Sphere        GetCollisionSphere() const { return mCollisionSphere; }  // 当たり判定球を返却（持っていれば）
		Capsule       GetCollisionCapsule()const { return mCollisionCapsule; } // 当たり判定カプセルを返却（持っていれば）
		int           GetCollisionModel() const  { return mCollisionModel; }   // 当たり判定モデルを返却（持っていれば)

	protected:
		void          DrawCollider();
		void          CollisionUpdate();                           // 当たり判定位置の更新
		ObjectTag     mTag;                                        // このゲームオブジェクトのオブジェクト種類
		VECTOR        mPos;                                        // オブジェクト位置
		int           mModelHandle;                                // モデルハンドル
		bool          mVisible;                                    // 可視状態
		bool          mAlive;                                      // 生死状態

		// 当たり判定関連
		CollisionType mCollisionType;                              // 当たり判定タイプ
		LineSegment   mCollisionLine;                              // 当たり判定Line
		Sphere        mCollisionSphere;                            // 当たり判定球
		Capsule       mCollisionCapsule;                           // 当たり判定カプセル
		int           mCollisionModel;                             // 当たり判定用モデル（表示モデルと別に簡易当たり判定モデルをセット）
	};

}// namespace My3dApp