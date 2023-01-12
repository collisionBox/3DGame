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
	// 動的シングルトン.
	/*static PlayerCannon& Instance() { return *instance; }
	static void CreateInstance();
	static void DereteInstance();*/

	PlayerCannon(ObjectBase* body, int inputState);
	~PlayerCannon();


	void Update(float deltaTime);// 更新.
	//void Update(float deltaTime) override;
	void Draw();// 描画.

	


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


