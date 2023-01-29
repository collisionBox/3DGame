#pragma once
#include "foundation.h"
#include "EnemyCannon.h"
class EnemyBody:
	public ObjectBase
{
public:
	EnemyBody(VECTOR initPos, VECTOR initDir, const char* failName);
	~EnemyBody();

	void Update(float deltaTime);
	void OnCollisionEnter(const ObjectBase* other);
	void Draw();
private:
	void MoveMethod(float deltaTime);
	void Rotate(float degree);
	VECTOR aimDir;
	VECTOR velocity;
	bool rotateNow;
	float time;
	int rand;

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

	class EnemyCannon* cannon;


	static int corner;
	bool stopWhenSeeEnemy;
};

