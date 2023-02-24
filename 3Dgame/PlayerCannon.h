#pragma once
#include "foundation.h"
#include "Camera.h"
#include "BulletManager.h"

class PlayerCannon : public ObjectBase
{
public:
	//static PlayerCannon& Instance() { static PlayerCannon instance; return instance; }
	
	PlayerCannon(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag userTag, const char* failName);
	~PlayerCannon();



	void Update(float deltaTime);// 更新.
	void Updateeeee(VECTOR bodyPos, float deltaTime);
	void Draw();// 描画.


	VECTOR GetPos() const { return pos; }
	VECTOR GetDir() const { return dir; }

	void Initialize(VECTOR initPos, VECTOR initDir);
	void Input(float deltaTime, XINPUT_STATE pad);
private:
	void Rotate();
	
	VECTOR aimDir;
	bool rotateNow;
	int padInput;
	const float TurnPerformance = 3.50f;// 旋回性能.
	const float adjustPos = 0.5f;
	class BulletManager* bulletManager;
};


