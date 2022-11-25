#pragma once
#include "DxLib.h"
class camera
{
public:
	camera();
	~camera();

	void Update(float deltaTime);

	void SetRotateZAngle(float angle) { rotateZAngle = angle; }
	void SetlookDownAngle(float angle) { lookDownAngle = angle; }
	void SetLength(float length) { this->length = length; }
	void SetPos(VECTOR vec) { pos = vec; }

	VECTOR& GetForwardVec() { return forwardVec; }
	VECTOR& GetPos() { return pos; }

private:
	float length;//距離
	float rotateZAngle;//カメラ周囲回転方向回転角.
	float lookDownAngle;//カメラ見下ろし方向回転角.
	VECTOR pos;//ポジション.
	VECTOR forwardVec//前方方向.
	
};

