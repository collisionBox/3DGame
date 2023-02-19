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
	void MoveMethod(float deltaTime);// �ړ�����.
	void Rotate(float degree);// ��]����.
	VECTOR aimDir;
	VECTOR velocity;
	bool rotateNow;
	float time;
	int rand;

	static const float Accel;// �O�i�����x.
	static const float Back;// ��i�����x.
	static const float MaxSpeed;// �ō��O�i���x.
	static const float MinSpeed;// �ō��X�V���x.
	float accel;

	class EnemyCannon* cannon;

};

