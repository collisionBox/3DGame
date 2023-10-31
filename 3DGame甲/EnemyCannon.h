#pragma once
#include "ObjectBase.h"
#include "Math.h"
#include <map>
class EnemyCannon : public ObjectBase
{
public:
	EnemyCannon(VECTOR initPos, VECTOR initDir, ObjectTag userTag);
	~EnemyCannon();
	void Update(float deltaTime) {};// �X�V(�s�g�p).
	void Updateeeee(VECTOR bodyPos, float deltaTime);// �X�V.
	void Draw();// �`��.
	void Initialize(VECTOR initPos, VECTOR initDir);
private:
	void Rotate(float deltaTime);
	bool Search(VECTOR playerPos);
	void DiviationValculation(float deltaTime);
	void Fire();
	VECTOR aimDir;
	bool rotateNow;
	int padInput;
	const float TurnPerformance = 3.50f;// ���񐫔\.
	const float AdjustPos = 0.5f;
	const float ShotIntervalTime = 2.5f;
	const float Omega = 40.0f;// ��C���񑬓x.
	float shotTime;
	const float RadarRange = ToRadian(150.0f);
	const float Radius = 50.0f;
	ObjectTag userTag;
	VECTOR jbPlayerPos;// ���O�̃v���C���[�ʒu.jb=just before
	int stageNum;
	const float FOVDegree = 5.0f;
	VECTOR a;
};

