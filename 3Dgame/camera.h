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
	//float length;//����
	//float rotateZAngle;//�J�������͉�]������]�p.
	//float lookDownAngle;//�J���������낵������]�p.
	VECTOR pos;//�|�W�V����.
	VECTOR targetPos;//�J�������ړ_.
	VECTOR camOffset;//�v���C���[����̑��Έʒu.
	VECTOR aimPos;// �ڕW�ʒu.
	VECTOR aimTargetPos;// ���ړ_�ڕW.
	//VECTOR forwardVec;//�O������.
	
};

