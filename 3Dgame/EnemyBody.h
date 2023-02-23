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

	const float Accel = 6.0f;// �ʏ�̉���.
	const float Back = 5.0f;// ��ޑ��x.
	const float MaxSpeed = 200.0f;// �ō��O�i���x.
	const float MinSpeed = -350.0f;// �ō���ޑ��x.
	const float DefaultDecel = 0.97f;// �Ȃɂ����Ȃ����̌���.
	const float BreakDecel = 0.5f;// �u���[�L���̌���.
	const float GripDecel = -5.0f;// �O���b�v�̌���.
	const float GripPower = 2.0f;// �O���b�v��.
	const float ColideDecelFac = 4.0f;// ��Q���ɂԂ������Ƃ��̌�����.
	const float TurnPerformance = 5.0f;// ���񐫔\.
	float accel;

	class EnemyCannon* cannon;


	static int corner;
	bool stopWhenSeeEnemy;
};

