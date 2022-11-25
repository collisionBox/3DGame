#include "camera.h"
#include "player.h"
camera::camera()
{
	SetCameraNearFar(0.1f, 1000.0f);
	pos = VGet(0, 0, 0);

}

camera::~camera()
{
}

void camera::Update(float deltaTime)
{
#if 1
	VECTOR aimPos = VAdd(player::GetInstance().GetPos(), VScale(player::GetInstance().GetDir(), -30.0f));
	aimPos = VAdd(aimPos, VGet(0, 20.0f, 0));
	VECTOR posToAim = VSub(aimPos, pos);
	VECTOR scaledPosToAim = VScale(posToAim, 0.1f);
	pos = VAdd(pos, scaledPosToAim);
	SetCameraPositionAndTarget_UpVecY(pos, player::GetInstance().GetPos());
#else
	const float dumper = 1.5f;
	VECTOR diff;
	VECTOR playerPos

#endif // 0

	
}
