#pragma once
#include "foundation.h"
#include "PlayerCannon.h"
#include "HPGauge.h"
class PlayerBody :
	public ObjectBase
{
public:
	PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag myTag, const char* failName);
	~PlayerBody();

	//static PlayerBody& Instance() { static PlayerBody body; return body; }

	void Update(float deltaTime) override;// �X�V.
	void Draw() override;// �`��.
	void OnCollisionEnter(const ObjectBase* other) override;



private:
	void Input(float deltaTime);
	void Rotate();


	VECTOR aimDir;// �ڕW����.
	VECTOR velocity;// �����x�N�g��.
	VECTOR prevPos; // �\���|�W�V����.
	bool rotateNow;// ��]���Ă��邩�ǂ���.
	float deltaWaitTime;
	float accel;
	// �R���g���[���[�ϐ�.
	int padInput;
	XINPUT_STATE pad;

	class PlayerCannon* cannon;
	class HPGauge* hpGauge;

	// �ÓI�֐�.
	const float Accel = 6.0f;// �ʏ�̉���.
	const float Back = 5.0f;// ��ޑ��x.
	const float MaxSpeed = 300.0f;// �ō��O�i���x.
	const float MinSpeed = -200.0f;// �ō���ޑ��x.
	const float DefaultDecel = 0.97f;// �Ȃɂ����Ȃ����̌���.
	const float BreakDecel = 0.5f;// �u���[�L���̌���.
	const float GripDecel = -5.0f;// �O���b�v�̌���.
	const float TurnPerformance = 5.0f;// ���񐫔\.
	const float OnShootingDownWaitTime = 5.0f;// �팂�Ď��ҋ@����.

};

