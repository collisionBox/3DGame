#pragma once
#include "DxLib.h"
#include "ObjectBase.h"

class PlayerBody : public ObjectBase
{
public:
	PlayerBody();
	~PlayerBody();

	static PlayerBody& Instance() { static PlayerBody body; return body; }

	void Update(float deltaTime) override;// �X�V.
	void Draw() override;// �`��.
	void OnCollisionEnter(const ObjectBase* other) override;

private:
	void Input(float deltaTime);
	void Rotate();
	VECTOR dir;
	VECTOR aimDir;
	VECTOR velocity;

	bool rotateNow;

};

