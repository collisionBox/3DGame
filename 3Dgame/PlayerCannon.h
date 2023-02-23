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


	void Update(float deltaTime);// çXêV.
	void Updateeeee(VECTOR bodyPos, float deltaTime);
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
	const float TurnPerformance = 3.50f;// ê˘âÒë¨ìx.
	class BulletManager* bulletManager;
};


