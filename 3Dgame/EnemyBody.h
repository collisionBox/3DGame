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
	float time;// タイムカウンター.
	int rand;// ランダム値.

	float accel;

	class EnemyCannon* cannon;


	int corner;
	bool stopWhenSeeEnemy;

	const float Accel = 6.0f;// 通常の加速.
	const float Back = 5.0f;// 後退速度.
	const float MaxSpeed = 200.0f;// 最高前進速度.
	const float MinSpeed = -350.0f;// 最高後退速度.
	const float ColideDecelFac = 4.0f;// 障害物にぶつかったときの減速率.
	const float TurnPerformance = 5.0f;// 旋回性能.
};

