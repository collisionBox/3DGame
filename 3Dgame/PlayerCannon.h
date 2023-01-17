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
	//static PlayerCannon& Instance() { static PlayerCannon instance; return instance; }
	
	PlayerCannon(class PlayerBody* body, int inputState, ObjectTag userTag, ObjectTag myTag);
	~PlayerCannon();


	void Update(float deltaTime);// çXêV.
	//void Update(float deltaTime) override;
	void Draw();// ï`âÊ.


	VECTOR GetPos() const { return pos; }
	VECTOR GetDir() const { return dir; }
private:
	void Input(float deltaTime);
	void Rotate();
	VECTOR aimDir;
	bool rotateNow;
	int padInput;
	XINPUT_STATE pad;
	ObjectTag tag;
	static const float TurnPerformance;

};


