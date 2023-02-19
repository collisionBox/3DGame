#pragma once
#include "foundation.h"
#include "PlayerCannon.h"
#include "HPGauge.h"
class PlayerBody :
	public ObjectBase
{
public:
	PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, PlayerTag myTag, const char* failName);
	~PlayerBody();

	//static PlayerBody& Instance() { static PlayerBody body; return body; }

	void Update(float deltaTime) override;// �X�V.
	void Draw() override;// �`��.
	void OnCollisionEnter(const ObjectBase* other) override;

	const PlayerTag GetPlayerTag() const { return playerTag; }

private:
	void Input(float deltaTime);
	void Rotate();


	VECTOR aimDir;// �ڕW����.
	VECTOR velocity;// �����x�N�g��.
	VECTOR prevPos; // �\���|�W�V����.
	bool rotateNow;// ��]���Ă��邩�ǂ���.
	float deltaWaitTime;
	float accel;
	PlayerTag playerTag;

	// �R���g���[���[�ϐ�.
	int padInput;
	XINPUT_STATE pad;

	class PlayerCannon* cannon;
	class HPGauge* hpGauge;

	// �ÓI�֐�.
	static const float Accel;// �O�i�����x.
	static const float Back;// .��މ����x
	static const float MaxSpeed;// �ő�O�i���x.
	static const float MinSpeed;// �ő�X�V���x.
	static const float OnShootingDownWaitTime;// �팂�Ď��ҋ@����.
	const float DefaultDecel = 0.97f;// �Ȃɂ����Ȃ����̌���.
	const float GripDecel = -5.0f;// �O���b�v�̌���.
	const float TurnPerformance = 5.0f;// ���񐫔\.

};

