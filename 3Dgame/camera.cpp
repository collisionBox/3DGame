#include "Camera.h"
#include "ObjectTag.h"
#include "ObjectManager.h"
#include "PlayerBody.h"

const float springSterength = 50.0f;

MainCamera::MainCamera()
	:ObjectBase(ObjectTag::Camera)
	,targetPos()
	,camOffset()
	,aimPos()
{
	
	pitch = 0;
	yaw = 0;
	pos = VGet(0.0f, 870.0f, -0.1f);
	float fov = 60 * DX_PI_F / 180;
	SetupCamera_Perspective(fov);
	//奥行0.1〜3000までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 3000.0f);
	aimTargetPos = VGet(0.0f, 0.0f, 0.0f);
	SetCameraPositionAndTarget_UpVecY(pos, aimTargetPos);
	// 変数の初期化.

}

const float maxPitch = 89.0f * DX_PI_F / 180.0f;
//MainCamera::MainCamera(PlayerBody* body)
//	: ObjectBase(ObjectTag::Camera)
//	, targetPos()
//	, camOffset()
//	, aimPos()
//	, aimTargetPos()
//{
//	pos = VAdd(body->GetPos(), VGet(0.0f, 10.0f, 0.0f));
//	yaw = 0;
//	pitch = 0;
//	SetCameraPositionAndTarget_UpVecY(VGet(0, 100, 0), body->GetPos());
//	奥行0.1〜3000までをカメラの描画範囲とする
//	SetCameraNearFar(0.1f, 3000.0f);
//}

void MainCamera::Update(float deltaTime)
{
	ObjectBase* body = ObjectManager::GetFirstObject(ObjectTag::Body);
	ObjectBase* cannon = ObjectManager::GetFirstObject(ObjectTag::Cannon);
#if 0
	
		aimTargetPos = body->GetPos();
		aimPos = aimTargetPos + camOffset;
		const float add = 2.0f;
		const float length = 200.0f;

		if (CheckHitKey(KEY_INPUT_W))
		{
			pitch -= add * deltaTime;
		}
		if (CheckHitKey(KEY_INPUT_S))
		{
			pitch += add * deltaTime;
		}
		if (CheckHitKey(KEY_INPUT_A))
		{
			yaw += add * deltaTime;
		}
		if (CheckHitKey(KEY_INPUT_D))
		{
			yaw -= add * deltaTime;
		}
		if (pitch > maxPitch)
		{
			pitch = maxPitch;
		}
		if (pitch < 0)
		{
			pitch = 0;
		}
		if (yaw > 360)
		{
			yaw = 0;
		}
		// yaw計算.
		pos.x = length * cosf(yaw);
		pos.z = length * sinf(yaw);
		// pitch計算
		pos.x *= cosf(pitch);
		pos.y = length * sinf(pitch);
		pos.z *= cosf(pitch);
		// プレイヤー座標を加算.
		pos = VAdd(pos, aimTargetPos);
		dir = VSub(aimTargetPos, pos);
		dir = VNorm(dir);
		SetCameraPositionAndTarget_UpVecY(pos, body->GetPos());

#else
	if (CheckHitKey(KEY_INPUT_W))
	{
		pos.y -= 10;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		pos.y += 10;
	}
	SetCameraPositionAndTarget_UpVecY(pos, aimTargetPos);

#endif
		//
	

}
