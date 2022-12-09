#pragma once

#include <DxLib.h>
#include "math3D.h"

namespace My3dApp
{
	// @brief 線分当たり判定.
	struct LineSegment
	{
		LineSegment();
		LineSegment(const VECTOR& startPos, const VECTOR& endPos);
		void Move(const VECTOR& pos);

		VECTOR mLocalStart; // 線分のローカル開始座標 ローカル座標とはGameObjectを(0,0,0)としたときの相対位置
		VECTOR mLocalEnd;   // 線分のローカル終了座標
		VECTOR mWorldStart; // 線分のワールド開始座標 ワールド座標とはGameObjectの位置+ローカル開始座標のこと。当たり判定ではこちらが使用される
		VECTOR mWorldEnd;   // 線分のワールド終了座標
	};

	// @brief 球体当たり判定.
	struct Sphere
	{
		Sphere();
		Sphere(const VECTOR& center, float radius);
		void Move(const VECTOR& pos);

		VECTOR mLocalCenter; // 球体のローカル中心座標
		VECTOR mWorldCenter; // 球体のワールド中心座標
		float  mRadius;      // 球体の半径
	};

	// @brief カプセル当たり判定.
	struct Capsule
	{
		Capsule();
		Capsule(const VECTOR& start, const VECTOR& end, float radius);
		void Move(const VECTOR& pos);

		VECTOR mLocalStart; // カプセルのローカル開始座標
		VECTOR mLocalEnd;   // カプセルのローカル終了座標
		VECTOR mWorldStart; // カプセルのワールド開始座標
		VECTOR mWorldEnd;   // カプセルのワールド終了座標
		float  mRadius;     // カプセルの半径
	};

	// 当たり判定の関数組み合わせ
	bool CollisionPair(const Sphere&       sphere1, const Sphere&      sphere2);
	bool CollisionPair(const LineSegment&  line   , const Sphere&      sphere);
	bool CollisionPair(const Sphere&       sphere , const LineSegment& line);
	bool CollisionPair(const Sphere&       sphere,  int modelHandle, MV1_COLL_RESULT_POLY_DIM& collisionInfo);
	bool CollisionPair(const LineSegment& line, const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo);
	bool CollisionPair(const int modelHandle, const LineSegment& line, MV1_COLL_RESULT_POLY& collisionInfo);

	// @brief 球体とメッシュとの当たり押し戻し量計算
	VECTOR CalcSpherePushBackVecFromMesh(const My3dApp::Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo);

}// namespace My3dApp