#include "Camera.h"
#include "ObjectTag.h"
#include "ObjectManager.h"
#include "PlayerBody.h"


MainCamera::MainCamera()
	:ObjectBase(ObjectTag::Camera)
{
	
	pos = VGet(0.0f, 870.0f, -0.1f);
	float fov = 60 * DX_PI_F / 180;
	SetupCamera_Perspective(fov);
	//奥行0.1〜3000までをカメラの描画範囲とする
	SetCameraNearFar(0.1f, 3000.0f);
	aimTargetPos = VGet(0.0f, 0.0f, 0.0f);
	SetCameraPositionAndTarget_UpVecY(pos, aimTargetPos);
	// 変数の初期化.

}


void MainCamera::Update(float deltaTime)
{
	if (CheckHitKey(KEY_INPUT_W))
	{
		pos.y -= 10;
	}
	if (CheckHitKey(KEY_INPUT_S))
	{
		pos.y += 10;
	}
	SetCameraPositionAndTarget_UpVecY(pos, aimTargetPos);

	

}
