#include "Camera.h"
#include "ObjectTag.h"
#include "ObjectManager.h"
#include "PlayerBody.h"

const float springSterength = 2.0f;

MainCamera::MainCamera(float camHeigth, float camZPos)
	:ObjectBase(ObjectTag::Camera)
	,pos()
	,targetPos()
	,camOffset()
	,aimPos()
	,aimTargetPos()
{
	camOffset.x = 0;
	camOffset.y = camHeigth;
	camOffset.z = camZPos;

}


void MainCamera::Update(float deltaTime)
{
	ObjectBase* player = ObjectManager::GetFirstObject(ObjectTag::Player);
	if (player)
	{
		aimTargetPos = player->GetPos();
		aimPos = aimTargetPos + camOffset;

		VECTOR lookMoveDir = aimTargetPos - targetPos;
		VECTOR posMoveDir = aimPos - pos;

		targetPos += lookMoveDir * springSterength * deltaTime;
		pos += posMoveDir * springSterength * deltaTime;

		SetCameraPositionAndTarget_UpVecY(pos, targetPos);
	}
}
