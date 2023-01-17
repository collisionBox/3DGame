#pragma once
#include "foundation.h"

class EnemyBody:
	public ObjectBase
{
public:
	EnemyBody(VECTOR initPos, VECTOR initDir);
	~EnemyBody();

	void Update(float deltaTime);
	void Draw();
private:
	void Rotate(float degree);
	VECTOR aimDir;
	VECTOR velocity;
	bool rotateNow;
	float time;

	static const float Accel;
	static const float Back;
	static const float MaxSpeed;
	static const float MinSpeed;
	static const float DefaultDecel;
	static const float BreakDecel;
	static const float GripDecel;
	static const float GripPower;
	static const float ColideDecelFac;
	static const float TurnPerformance;
	float accel;
};

