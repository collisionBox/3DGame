#include "Collision.h"

namespace My3dApp
{
	//-----------------------------------------------------------------------------
	// @brief 線分コンストラクタ
	//-----------------------------------------------------------------------------
	LineSegment::LineSegment()
		: mLocalStart()
		, mLocalEnd()
		, mWorldStart()
		, mWorldEnd()
	{
	}

	//-----------------------------------------------------------------------------
	// @brief 線分コンストラクタ初期位置セット
	//-----------------------------------------------------------------------------
	LineSegment::LineSegment(const VECTOR& start, const VECTOR& end)
		: mLocalStart(start)
		, mLocalEnd(end)
		, mWorldStart(start)
		, mWorldEnd(end)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief 線分のワールド位置を移動する
	//-----------------------------------------------------------------------------
	void LineSegment::Move(const VECTOR& pos)
	{
		mWorldStart = mLocalStart + pos;
		mWorldEnd = mLocalEnd + pos;
	}

	//-----------------------------------------------------------------------------
	// @brief 球体コンストラクタ
	//-----------------------------------------------------------------------------
	Sphere::Sphere()
		: mLocalCenter()
		, mWorldCenter()
		, mRadius(0.0f)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief 球体コンストラクタ
	//-----------------------------------------------------------------------------
	Sphere::Sphere(const VECTOR& center, float radius)
		: mLocalCenter(center)
		, mWorldCenter(center)
		, mRadius(radius)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief 球体のワールド座標を移動する
	//-----------------------------------------------------------------------------
	void Sphere::Move(const VECTOR& pos)
	{
		mWorldCenter = mLocalCenter + pos;
	}

	//-----------------------------------------------------------------------------
	// @brief カプセル当たり判定コンストラクタ
	//-----------------------------------------------------------------------------
	Capsule::Capsule()
		: mLocalStart()
		, mLocalEnd()
		, mWorldStart()
		, mWorldEnd()
		, mRadius(0.0f)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief カプセル当たり判定コンストラクタ
	//-----------------------------------------------------------------------------
	Capsule::Capsule(const VECTOR& start, const VECTOR& end, float radius)
		: mLocalStart(start)
		, mLocalEnd(end)
		, mWorldStart(start)
		, mWorldEnd(end)
		, mRadius(0.0f)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief カプセルのワールド座標を移動する
	//-----------------------------------------------------------------------------
	void Capsule::Move(const VECTOR& pos)
	{
		mWorldStart = mLocalStart + pos;
		mWorldEnd = mLocalEnd + pos;
	}

	//-----------------------------------------------------------------------------
	// @brief 当たり判定 球・球
	// @param[in] sphere1 球
	// @param[in] sphere2 球
	// @return bool 球同士がぶつかっている場合はtrue を返す
	//-----------------------------------------------------------------------------
	bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2)
	{
		return HitCheck_Sphere_Sphere(sphere1.mWorldCenter, sphere1.mRadius, sphere2.mWorldCenter, sphere2.mRadius);
	}

	//-----------------------------------------------------------------------------
	// @brief 当たり判定 線分・球
	// @param[in] line1 線分
	// @param[in] sphere1 球
	// @return bool 線分と球がぶつかっている場合はtrue を返す
	//-----------------------------------------------------------------------------
	bool CollisionPair(const LineSegment& line, const Sphere& sphere)
	{
		return HitCheck_Line_Sphere(line.mWorldStart, line.mWorldEnd, sphere.mWorldCenter, sphere.mRadius);
	}

	//-----------------------------------------------------------------------------
	// @brief 当たり判定 線分・球
	// @param[in] sphere 球
	// @param[in] line 線分
	// @return bool 球と線分がぶつかっている場合はtrue を返す
	//-----------------------------------------------------------------------------
	bool CollisionPair(const Sphere& sphere, const LineSegment& line)
	{
		return HitCheck_Line_Sphere(line.mWorldStart, line.mWorldEnd, sphere.mWorldCenter, sphere.mRadius);
	}

	//-----------------------------------------------------------------------------
	// @brief 当たり判定 線分・メッシュ
	// @param[in]  line          線分
	// @param[in]  modelHandle   メッシュのモデルID
	// @param[out] collisionInfo 当たった場合のポリゴン数、ポリゴンリスト
	// @return     線分とモデルが衝突している場合はtrueを返す。collisionInfoに当たり判定詳細情報が返る
	//-----------------------------------------------------------------------------
	bool CollisionPair(const LineSegment& line, const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo)
	{
		collisionInfo = MV1CollCheck_Line(modelHandle, -1, line.mWorldStart, line.mWorldEnd);
		return collisionInfo.HitFlag;
	}

	//-----------------------------------------------------------------------------
	// @brief 当たり判定 メッシュ・線分
	// @param[in]  modelHandle   メッシュのモデルID
	// @param[in]  line          線分
	// @param[out] collisionInfo 当たった場合のポリゴン数、ポリゴンリスト
	// @return     線分とモデルが衝突している場合はtrueを返す。collisionInfoに当たり判定詳細情報が返る
	// @detail     線分とモデル衝突の当たり判定引数が逆バージョン
	//-----------------------------------------------------------------------------
	bool CollisionPair(const int modelHandle, const LineSegment& line, MV1_COLL_RESULT_POLY& collisionInfo)
	{
		return CollisionPair(line, modelHandle, collisionInfo);
	}

	//-----------------------------------------------------------------------------
	// @brief 当たり判定 球・メッシュ
	// @param[in]  sphere        球
	// @param[in]  modelHandle   メッシュのモデルID
	// @param[out] collisionInfo 当たった場合のポリゴン数、ポリゴンリスト
	// @return     球とモデルが衝突している場合はtrueを返す
	//-----------------------------------------------------------------------------
	bool CollisionPair(const Sphere& sphere, int modelHandle, MV1_COLL_RESULT_POLY_DIM& collisionInfo)
	{
		collisionInfo = MV1CollCheck_Sphere(modelHandle, -1, sphere.mWorldCenter, sphere.mRadius);
		if (collisionInfo.HitNum == 0)
		{
			return false;
		}
		return true;
	}

	//-----------------------------------------------------------------------------
	// @brief 球体とメッシュとのめり込みを戻すベクトルを求める
	// @param[in] sphere 球体
	// @param[in] collisionInfo MV1CollCheck_Sphere()関数が返す衝突情報
	// @return VECTOR 球体がメッシュから離れる向きの移動ベクトルを返す
	//-----------------------------------------------------------------------------
	VECTOR CalcSpherePushBackVecFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo)
	{
		// 衝突球
		VECTOR moveCandidate = sphere.mWorldCenter; // 球中心候補 
		float  radius = sphere.mRadius; // 球半径
		VECTOR planeNormal;                    // ポリゴン平面法線
		VECTOR moveVec = VGet(0, 0, 0);    // 移動ベクトル
		float  moveLen = 0.0f;           // 移動量

		VECTOR newCenter = sphere.mWorldCenter; // 移動候補  

		int i = 0, j = 0;
		moveCandidate = sphere.mWorldCenter;

		// 衝突ポリゴンをすべて回って、球のめり込みを解消する
		for (i = 0; i < collisionInfo.HitNum; ++i)
		{
			// 衝突ポリゴンの辺 
			VECTOR edge1, edge2;
			edge1 = collisionInfo.Dim[i].Position[1] - collisionInfo.Dim[i].Position[0];
			edge2 = collisionInfo.Dim[i].Position[2] - collisionInfo.Dim[i].Position[0];

			// 衝突ポリゴンの辺より、ポリゴン面の法線ベクトルを求める
			planeNormal = VCross(edge1, edge2);
			planeNormal = VNorm(planeNormal);

			// 球中心に最も近いポリゴン平面の点を求める
			VECTOR tmp = moveCandidate - collisionInfo.Dim[i].Position[0];
			float  dot = VDot(planeNormal, tmp);

			// 衝突点
			VECTOR hitPos = moveCandidate - planeNormal * dot;

			// 球がどれくらいめり込んでいるかを算出
			VECTOR tmp2 = moveCandidate - hitPos;
			float  len = VSize(tmp2);

			// めり込んでいる場合は球の中心を押し戻し
			if (HitCheck_Sphere_Triangle(moveCandidate, radius,
				collisionInfo.Dim[i].Position[0],
				collisionInfo.Dim[i].Position[1],
				collisionInfo.Dim[i].Position[2]) == TRUE)
			{
				// めり込み解消する位置まで移動
				VECTOR moveVec;
				len = radius - len;
				//len += 0.0001f;
				moveVec = planeNormal * len;
				moveCandidate += moveVec;
			}
		}
		// 移動候補を移動位置にする
		newCenter = moveCandidate;

		// 押し戻し量を返却
		return newCenter - sphere.mWorldCenter;
	}

}// namespace My3dApp