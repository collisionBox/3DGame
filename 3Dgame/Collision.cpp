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
// @brief �����蔻�� ���E��
// @param[in] sphere1 ��
// @param[in] sphere2 ��
// @return bool �����m���Ԃ����Ă���ꍇ��true ��Ԃ�
//-----------------------------------------------------------------------------
bool CollisionPair(const Sphere& sphere1, const Sphere& sphere2)
{
	return HitCheck_Sphere_Sphere(sphere1.worldCenter, sphere1.radius, sphere2.worldCenter, sphere2.radius);
}

//-----------------------------------------------------------------------------
// @brief �����蔻�� �����E��
// @param[in] line1 ����
// @param[in] sphere1 ��
// @return bool �����Ƌ����Ԃ����Ă���ꍇ��true ��Ԃ�
//-----------------------------------------------------------------------------
bool CollisionPair(const LineSegment& line, const Sphere& sphere)
{
	return HitCheck_Line_Sphere(line.worldStart, line.worldEnd, sphere.worldCenter, sphere.radius);
}

//-----------------------------------------------------------------------------
// @brief �����蔻�� �����E��
// @param[in] sphere ��
// @param[in] line ����
// @return bool ���Ɛ������Ԃ����Ă���ꍇ��true ��Ԃ�
//-----------------------------------------------------------------------------
bool CollisionPair(const Sphere& sphere, const LineSegment& line)
{
	return HitCheck_Line_Sphere(line.worldStart, line.worldEnd, sphere.worldCenter, sphere.radius);
}

//-----------------------------------------------------------------------------
// @brief �����蔻�� �����E���b�V��
// @param[in]  line          ����
// @param[in]  modelHandle   ���b�V���̃��f��ID
// @param[out] collisionInfo ���������ꍇ�̃|���S�����A�|���S�����X�g
// @return     �����ƃ��f�����Փ˂��Ă���ꍇ��true��Ԃ��BcollisionInfo�ɓ����蔻��ڍ׏�񂪕Ԃ�
//-----------------------------------------------------------------------------
bool CollisionPair(const LineSegment& line, const int modelHandle, MV1_COLL_RESULT_POLY& collisionInfo)
{
	collisionInfo = MV1CollCheck_Line(modelHandle, -1, line.worldStart, line.worldEnd);
	return collisionInfo.HitFlag;
}

//-----------------------------------------------------------------------------
// @brief �����蔻�� ���b�V���E����
// @param[in]  modelHandle   ���b�V���̃��f��ID
// @param[in]  line          ����
// @param[out] collisionInfo ���������ꍇ�̃|���S�����A�|���S�����X�g
// @return     �����ƃ��f�����Փ˂��Ă���ꍇ��true��Ԃ��BcollisionInfo�ɓ����蔻��ڍ׏�񂪕Ԃ�
// @detail     �����ƃ��f���Փ˂̓����蔻��������t�o�[�W����
//-----------------------------------------------------------------------------
bool CollisionPair(const int modelHandle, const LineSegment& line, MV1_COLL_RESULT_POLY& collisionInfo)
{
	return CollisionPair(line, modelHandle, collisionInfo);
}

//-----------------------------------------------------------------------------
// @brief �����蔻�� ���E���b�V��
// @param[in]  sphere        ��
// @param[in]  modelHandle   ���b�V���̃��f��ID
// @param[out] collisionInfo ���������ꍇ�̃|���S�����A�|���S�����X�g
// @return     ���ƃ��f�����Փ˂��Ă���ꍇ��true��Ԃ�
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
	// �Փˋ�.
	VECTOR moveCandidate = sphere.worldCenter;// �����S���.
	float radius = sphere.radius;// �����a.
	VECTOR planeNormal;// �|���S�����ʖ@��.
	VECTOR moveVec = VGet(0, 0, 0);// �ړ��x�N�g��.
	float moveLen = 0.0f;// �ړ���.

	VECTOR newCenter = sphere.worldCenter;// �ړ����.
	int i = 0, j = 0;
	moveCandidate = sphere.worldCenter;

	// �Փ˃|���S�������ׂĉ���āA�e�̂߂荞�݂���������.
	for (int i = 0; i < collisionInfo.HitNum; ++i)
	{
		// �Փ˃|���S���̕�.
		VECTOR edge1, edge2;
		edge1 = collisionInfo.Dim[i].Position[1] - collisionInfo.Dim[i].Position[0];
		edge2 = collisionInfo.Dim[i].Position[2] - collisionInfo.Dim[i].Position[0];


		// �Փ˃|���S���̕ӂ��A�|���S���ʂ̖@��x�N�g�������߂�.
		planeNormal = VCross(edge1, edge2);
		planeNormal = VNorm(planeNormal);

		// �����S�ɍł��߂��|���S�����ʂ̓_�����߂�.
		VECTOR tmp = moveCandidate = collisionInfo.Dim[i].Position[0];
		float dot = VDot(planeNormal, tmp);

		// �Փ˓_.
		VECTOR hitPos = moveCandidate - planeNormal * dot;

		// �����ǂꂭ�炢�߂荞��ł��邩�Z�o.
		VECTOR tmp2 = moveCandidate - hitPos;
		float len = VSize(tmp2);

		// �߂荞��ł���ꍇ�͋��̒��S�������߂�.
		if (HitCheck_Sphere_Triangle(moveCandidate, radius,
			collisionInfo.Dim[i].Position[0],
			collisionInfo.Dim[i].Position[1],
			collisionInfo.Dim[i].Position[2]) == TRUE)
		{
			// �߂荞�݂���������ʒu�܂ňړ�.
			VECTOR moveVec;
			len = radius - len;
			moveVec = planeNormal * len;
			moveCandidate += moveVec;
		}
		// �ړ������ړ��ʒu�ɂ���.
		newCenter = moveCandidate;

		// �����߂��ʂ�ԋp.
		return newCenter - sphere.worldCenter;

	}

}

