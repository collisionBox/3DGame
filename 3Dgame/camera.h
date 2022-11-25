#pragma once
#include "DxLib.h"
class camera
{
public:
	camera();
	~camera();

	void Update(float deltaTime);

	void SetRotateZAngle(float angle) { rotateZAngle = angle; }
	void SetlookDownAngle(float angle) { lookDownAngle = angle; }
	void SetLength(float length) { this->length = length; }
	void SetPos(VECTOR vec) { pos = vec; }

	VECTOR& GetForwardVec() { return forwardVec; }
	VECTOR& GetPos() { return pos; }

private:
	float length;//����
	float rotateZAngle;//�J�������͉�]������]�p.
	float lookDownAngle;//�J���������낵������]�p.
	VECTOR pos;//�|�W�V����.
	VECTOR forwardVec//�O������.
	
};

