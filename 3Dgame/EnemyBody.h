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

	const float Accel = 6.0f;// 通常の加速.
	const float Back = 5.0f;// 後退速度.
	const float MaxSpeed = 200.0f;// 最高前進速度.
	const float MinSpeed = -350.0f;// 最高後退速度.
	const float DefaultDecel = 0.97f;// なにもしない時の減速.
	const float BreakDecel = 0.5f;// ブレーキ時の減速.
	const float GripDecel = -5.0f;// グリップの減速.
	const float GripPower = 2.0f;// グリップ力.
	const float ColideDecelFac = 4.0f;// 障害物にぶつかったときの減速率.
	const float TurnPerformance = 5.0f;// 旋回性能.
	float accel;

	class EnemyCannon* cannon;


	static int corner;
	bool stopWhenSeeEnemy;
};

