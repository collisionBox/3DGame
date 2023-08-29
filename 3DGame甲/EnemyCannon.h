#pragma once
#include "ObjectBase.h"
#include "Math.h"
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
	void Rotate();
	void Radar();
	void Fire();
	VECTOR aimDir;
	bool rotateNow;
	int padInput;
	const float TurnPerformance = 3.50f;// ���񐫔\.
	const float AdjustPos = 0.5f;
	const float ShotIntervalTime = 1.0f;
	const float Omega = 10.0f;
	float shotTime;
	const float RadarRange = ToRadian(150.0f);
	const float Radius = 50.0f;
	ObjectTag userTag;

};

