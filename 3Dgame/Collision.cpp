#include "Collision.h"

LineSegment::LineSegment()
	:localStart()
	,localEnd()
	,worldStart()
	,worldEnd()
{
}

LineSegment::LineSegment(const VECTOR& start, const VECTOR& end)
	:localStart(start)
	,localEnd(end)
	,worldStart(start)
	,worldEnd(end)
{
}

void LineSegment::Move(const VECTOR& pos)
{
	worldStart = localStart + pos;
	worldEnd = localEnd + pos;
}


Sphere::Sphere()
	:localCenter()
	, worldCenter()
	, radius(0.0f)
{
}

Sphere::Sphere(const VECTOR& center, float radius)
	:localCenter(center)
	,worldCenter(center)
	,radius(radius)
{
}

void Sphere::Move(const VECTOR& pos)
{
	worldCenter = localCenter + pos;
}

Capsuel::Capsuel()
	:localStart()
	,localEnd()
	,worldStart()
	,worldEnd()
	,radius(0.0f)
{
}

Capsuel::Capsuel(const VECTOR& start, const VECTOR& end, float radius)
	:localStart(start)
	,localEnd(end)
	,worldStart(start)
	,worldEnd(end)
	,radius(0.0f)
{
}

void Capsuel::Move(const VECTOR& pos)
{
	worldStart = localStart + pos;
	worldEnd = localEnd + pos;
}

//-----------------------------------------------------------------------------
// @brief 当たり判定 球・球
// @param[in] sphere1 球
// @param[in] sphere2 球
// @return bool 球同士がぶつかっている場合はtrue を返す
//-----------------------------------------------------------------------------
bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2)
{
	return HitCheck_Sphere_Sphere(sphere1.worldCenter, sphere1.radius, sphere2.worldCenter, sphere2.radius);
}

//-----------------------------------------------------------------------------
// @brief 当たり判定 線分・球
// @param[in] line1 線分
// @param[in] sphere1 球
// @return bool 線分と球がぶつかっている場合はtrue を返す
//-----------------------------------------------------------------------------
bool CollisionPair(const LineSegment& line, const Sphere& sphere)
{
	return HitCheck_Line_Sphere(line.worldStart, line.worldEnd, sphere.worldCenter, sphere.radius);
}

//-----------------------------------------------------------------------------
// @brief 当たり判定 線分・球
// @param[in] sphere 球
// @param[in] line 線分
// @return bool 球と線分がぶつかっている場合はtrue を返す
//-----------------------------------------------------------------------------
bool CollisionPair(const Sphere& sphere, const LineSegment& line)
{
	return HitCheck_Line_Sphere(line.worldStart, line.worldEnd, sphere.worldCenter, sphere.radius);
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
	collisionInfo = MV1CollCheck_Line(modelHandle, -1, line.worldStart, line.worldEnd);
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
	collisionInfo = MV1CollCheck_Sphere(modelHandle, -1, sphere.worldCenter, sphere.radius);
	if (collisionInfo.HitNum == 0)
	{
		return false;
	}
	return true;
}

VECTOR CalcSpherePushBackVecFromMesh(const Sphere& sphere, const MV1_COLL_RESULT_POLY_DIM& collisionInfo)
{
	// 衝突球.
	VECTOR moveCandidate = sphere.worldCenter;// 球中心候補.
	float radius = sphere.radius;// 球半径.
	VECTOR planeNormal;// ポリゴン平面法線.
	VECTOR moveVec = VGet(0, 0, 0);// 移動ベクトル.
	float moveLen = 0.0f;// 移動量.

	VECTOR newCenter = sphere.worldCenter;// 移動候補.
	int i = 0, j = 0;
	moveCandidate = sphere.worldCenter;

	// 衝突ポリゴンをすべて回って、弾のめり込みを解消する.
	for (int i = 0; i < collisionInfo.HitNum; ++i)
	{
		// 衝突ポリゴンの辺.
		VECTOR edge1, edge2;
		edge1 = collisionInfo.Dim[i].Position[1] - collisionInfo.Dim[i].Position[0];
		edge2 = collisionInfo.Dim[i].Position[2] - collisionInfo.Dim[i].Position[0];


		// 衝突ポリゴンの辺より、ポリゴン面の法専ベクトルを求める.
		planeNormal = VCross(edge1, edge2);
		planeNormal = VNorm(planeNormal);

		// 球中心に最も近いポリゴン平面の点を求める.
		VECTOR tmp = moveCandidate = collisionInfo.Dim[i].Position[0];
		float dot = VDot(planeNormal, tmp);

		// 衝突点.
		VECTOR hitPos = moveCandidate - planeNormal * dot;

		// 球がどれくらいめり込んでいるか算出.
		VECTOR tmp2 = moveCandidate - hitPos;
		float len = VSize(tmp2);

		// めり込んでいる場合は球の中心を押し戻し.
		if (HitCheck_Sphere_Triangle(moveCandidate, radius,
			collisionInfo.Dim[i].Position[0],
			collisionInfo.Dim[i].Position[1],
			collisionInfo.Dim[i].Position[2]) == TRUE)
		{
			// めり込みを解消する位置まで移動.
			VECTOR moveVec;
			len = radius - len;
			moveVec = planeNormal * len;
			moveCandidate += moveVec;
		}
		// 移動候補を移動位置にする.
		newCenter = moveCandidate;

		// 押し戻し量を返却.
		return newCenter - sphere.worldCenter;

	}

}

