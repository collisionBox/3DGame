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
	void MoveMethod(float deltaTime);// 移動処理.
	void Rotate(float degree);// 回転処理.
	VECTOR aimDir;
	VECTOR velocity;
	bool rotateNow;
	float time;
	int rand;

	static const float Accel;// 前進加速度.
	static const float Back;// 後進加速度.
	static const float MaxSpeed;// 最高前進速度.
	static const float MinSpeed;// 最高更新速度.
	float accel;

	class EnemyCannon* cannon;

};

