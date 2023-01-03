#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "PlayerCannon.h"

class PlayerBody :
	public ObjectBase
{
public:
	PlayerBody();
	~PlayerBody();

	static PlayerBody& Instance() { static PlayerBody body; return body; }

	void Update(float deltaTime) override;// �X�V.
	void Draw() override;// �`��.
	void OnCollisionEnter(const ObjectBase* other) override;


	VECTOR velocity;
private:
	void Input(float deltaTime);
	void Rotate();
	VECTOR aimDir;

	PlayerCannon* cannon;

	bool rotateNow;

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
	float accel;

};

