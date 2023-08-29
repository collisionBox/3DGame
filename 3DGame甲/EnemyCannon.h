#pragma once
#include "ObjectBase.h"
#include "Math.h"
class EnemyCannon : public ObjectBase
{
public:
	EnemyCannon(VECTOR initPos, VECTOR initDir, ObjectTag userTag);
	~EnemyCannon();
	void Update(float deltaTime) {};// 更新(不使用).
	void Updateeeee(VECTOR bodyPos, float deltaTime);// 更新.
	void Draw();// 描画.
	void Initialize(VECTOR initPos, VECTOR initDir);

private:
	void Rotate();
	void Radar();
	void Fire();
	VECTOR aimDir;
	bool rotateNow;
	int padInput;
	const float TurnPerformance = 3.50f;// 旋回性能.
	const float AdjustPos = 0.5f;
	const float ShotIntervalTime = 1.0f;
	const float Omega = 10.0f;
	float shotTime;
	const float RadarRange = ToRadian(150.0f);
	const float Radius = 50.0f;
	ObjectTag userTag;

};

