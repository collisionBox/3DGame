#pragma once
#include "foundation.h"
#include "PlayerCannon.h"

class PlayerBody :
	public ObjectBase
{
public:
	PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag myTag);
	~PlayerBody();

	//static PlayerBody& Instance() { static PlayerBody body; return body; }

	void Update(float deltaTime) override;// �X�V.
	void Draw() override;// �`��.
	void OnCollisionEnter(const ObjectBase* other) override;



private:
	void Input(float deltaTime);
	void Rotate();
	VECTOR aimDir;

	VECTOR velocity;
	bool rotateNow;
	bool onHitFlag;
	int padInput;
	XINPUT_STATE pad;

	class PlayerCannon* cannon;
	
	// �ÓI�֐�.
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

