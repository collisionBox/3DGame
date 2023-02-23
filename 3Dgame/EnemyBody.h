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
	float time;// �^�C���J�E���^�[.
	int rand;// �����_���l.

	float accel;

	class EnemyCannon* cannon;


	int corner;
	bool stopWhenSeeEnemy;

	const float Accel = 6.0f;// �ʏ�̉���.
	const float Back = 5.0f;// ��ޑ��x.
	const float MaxSpeed = 200.0f;// �ō��O�i���x.
	const float MinSpeed = -350.0f;// �ō���ޑ��x.
	const float ColideDecelFac = 4.0f;// ��Q���ɂԂ������Ƃ��̌�����.
	const float TurnPerformance = 5.0f;// ���񐫔\.
};

