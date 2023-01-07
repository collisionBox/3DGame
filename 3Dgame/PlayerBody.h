#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "AssetManager.h"
#include "Math.h"

class PlayerBody :
	public ObjectBase
{
public:
	PlayerBody();
	~PlayerBody();

	static PlayerBody& Instance() { static PlayerBody body; return body; }

	void Update(float deltaTime) override;// çXêV.
	void Draw() override;// ï`âÊ.
	void OnCollisionEnter(const ObjectBase* other) override;



private:
	void Input(float deltaTime);
	void Rotate();
	VECTOR aimDir;

	VECTOR velocity;
	bool rotateNow;

	// ê√ìIä÷êî.
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

