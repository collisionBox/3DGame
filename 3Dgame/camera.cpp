#include "Camera.h"
#include "ObjectTag.h"
#include "ObjectManager.h"
#include "PlayerBody.h"

const float springSterength = 50.0f;

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
	//‰œs0.1`3000‚Ü‚Å‚ðƒJƒƒ‰‚Ì•`‰æ”ÍˆÍ‚Æ‚·‚é
	SetCameraNearFar(0.1f, 3000.0f);

}


void MainCamera::Update(float deltaTime)
{
	ObjectBase* player = ObjectManager::GetFirstObject(ObjectTag::Player);
	if (player)
	{
#if 1
		aimTargetPos = player->GetPos();
		aimPos = aimTargetPos + camOffset;

		VECTOR lookMoveDir = aimTargetPos - targetPos;
		VECTOR posMoveDir = aimPos - pos;

		targetPos += lookMoveDir * springSterength * deltaTime;
		pos += posMoveDir * springSterength * deltaTime;
		//targetPos += lookMoveDir * deltaTime;
		//pos += posMoveDir * deltaTime;
		if (CheckHitKey(KEY_INPUT_W))
		{
			camOffset = VAdd(pos, VGet(0.0f, 100.0f, 0.0f));
		}
#else

		aimTargetPos = player->GetPos();
		aimPos = aimTargetPos + camOffset;

		VECTOR lookMoveDir = aimTargetPos - targetPos;
		VECTOR posMoveDir = aimPos - pos;

#endif
		SetCameraPositionAndTarget_UpVecY(pos, targetPos);

	}
	

}
