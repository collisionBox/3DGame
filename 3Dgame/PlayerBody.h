#pragma once
#include "DxLib.h"
#include "ObjectBase.h"

class PlayerBody : public ObjectBase
{
public:
	PlayerBody();
	~PlayerBody();

	static PlayerBody& instance() { static PlayerBody body; return body; }

	void Update(float deltaTime) override;// �X�V.
	void Draw() override;// �`��.
	void OnCollisionEnter(const ObjectBase* other) override;
	VECTOR velocity;
	VECTOR dir;

private:
	void Input(float deltaTime);
	void Rotate();
	VECTOR aimDir;

	bool rotateNow;

	// �ÓI�֐�.
	static const float Accel;
	static const float MaxSpeed;
	static const float DefaultDecel;
	static const float BreakDecel;
	static const float GripDecel;
	static const float GripPower;
	static const float ColideDecelFac;
	float decel;
};

