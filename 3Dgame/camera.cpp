#include "Camera.h"
#include "ObjectTag.h"
#include "ObjectManager.h"
#include "PlayerBody.h"

const float springSterength = 50.0f;

MainCamera::MainCamera(float pitchDegree, float yawDegree)
	:ObjectBase(ObjectTag::Camera)
	,pos()
	,targetPos()
	,camOffset()
	,aimPos()
	,aimTargetPos()
{
	this->pitch = ToRadian(pitchDegree);
	this->yaw = ToRadian(yawDegree);
	//���s0.1�`3000�܂ł��J�����̕`��͈͂Ƃ���
	SetCameraNearFar(1.0f, 3000.0f);

}

const float maxPitch = 89.0f * DX_PI_F / 180.0f;
void MainCamera::Update(float deltaTime)
{
	ObjectBase* player = ObjectManager::GetFirstObject(ObjectTag::Player);
	if (player)
	{
		aimTargetPos = player->GetPos();
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
		// yaw�v�Z.
		pos.x = length * cosf(yaw);
		pos.z = length * sinf(yaw);
		// pitch�v�Z
		pos.x *= cosf(pitch);
		pos.y = length * sinf(pitch);
		pos.z *= cosf(pitch);
		// �v���C���[���W�����Z.
		pos = VAdd(pos, aimTargetPos);
		dir = aimTargetPos - pos;
		SetCameraPositionAndTarget_UpVecY(pos, aimTargetPos);
	}
	

}
