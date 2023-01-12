#pragma once
#include "DxLib.h"
#include "ObjectBase.h"
#include "ObjectManager.h"
#include "AssetManager.h"
#include "PlayerBody.h"
#include "Camera.h"
#include "Math.h"
#include "Bullet.h"

class PlayerCannon : public ObjectBase
{
public:
	// ���I�V���O���g��.
	/*static PlayerCannon& Instance() { return *instance; }
	static void CreateInstance();
	static void DereteInstance();*/

	PlayerCannon(ObjectBase* body, int inputState);
	~PlayerCannon();


	void Update(float deltaTime);// �X�V.
	//void Update(float deltaTime) override;
	void Draw();// �`��.

	


	VECTOR GetPos() const { return pos; }
	VECTOR GetDir() const { return dir; }
	float monitorNum[3];
private:
	void Input(float deltaTime);
	void Rotate();
	VECTOR dirVec;
	VECTOR aimDir;
	bool rotateNow;
	int padInput;
	XINPUT_STATE pad;
	//static PlayerCannon* instance;

	static const float TurnPerformance;

};


