#pragma once
#include <DxLib.h>
#include "Math.h"
#include "ObjectBase.h"

class MainCamera : public ObjectBase
{
public:
	MainCamera(float camHeigth, float camZPos);

	void Update(float deltaTime);


private:
	//float length;//距離
	//float rotateZAngle;//カメラ周囲回転方向回転角.
	//float lookDownAngle;//カメラ見下ろし方向回転角.
	VECTOR pos;//ポジション.
	VECTOR targetPos;//カメラ注目点.
	VECTOR camOffset;//プレイヤーからの相対位置.
	VECTOR aimPos;// 目標位置.
	VECTOR aimTargetPos;// 注目点目標.
	//VECTOR forwardVec;//前方方向.
	
};

