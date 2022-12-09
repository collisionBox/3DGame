#include "Camera.h"
Camera::Camera()
{
	SetCameraNearFar(0.1f, 3000.0f);
	pos = VGet(0, 0, 0);

}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
#if 1

	//VECTOR aimPos = VAdd(Player::GetInstance().GetPos(), VScale(Player::GetInstance().GetDir(), -1000.0f));
	//aimPos = VAdd(aimPos, VGet(0, 300.0f, 0));
	//VECTOR posToAim = VSub(aimPos, pos);
	//VECTOR scaledPosToAim = VScale(posToAim, 0.1f);
	//pos = VAdd(pos, scaledPosToAim);

	SetCameraPositionAndTarget_UpVecY(pos, PlayerBody::Instance().GetPos());

#else
	const float dumper = 1.5f;
	VECTOR diff;
	VECTOR playerPos = Player::GetInstance().GetPos();

	diff = VSub(playerPos, viewTarget);
	diff.x = dumper * deltaTime * diff.x;
	diff.y = dumper * deltaTime * diff.y;
	diff.z = dumper * deltaTime * diff.z;
	const float rotate = 0.5f * deltaTime;
	if (CheckHitKey(KEY_INPUT_UP))
	{
		pos.y += 1.0f;
	}

	viewTarget = playerPos;
#endif // 0

	
}
