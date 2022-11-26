#include "Camera.h"
#include "Player.h"
Camera::Camera()
{
	SetCameraNearFar(0.1f, 1000.0f);
	pos = VGet(0, 0, 0);

}

Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
#if 1
	VECTOR aimPos = VAdd(Player::GetInstance().GetPos(), VScale(Player::GetInstance().GetDir(), -40.0f));
	aimPos = VAdd(aimPos, VGet(0, 30.0f, 0));
	VECTOR posToAim = VSub(aimPos, pos);
	VECTOR scaledPosToAim = VScale(posToAim, 0.1f);
	pos = VAdd(pos, scaledPosToAim);
	SetCameraPositionAndTarget_UpVecY(pos, Player::GetInstance().GetPos());

#else
	const float dumper = 1.5f;
	VECTOR diff;
	VECTOR playerPos

#endif // 0

	
}
