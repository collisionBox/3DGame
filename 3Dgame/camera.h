#pragma once
#include "Math.h"
#include "ObjectBase.h"

class MainCamera : public ObjectBase
{
public:
	MainCamera();

	void Update(float deltaTime);

private:

	VECTOR pos;//ポジション.
	VECTOR aimTargetPos;// 注目点目標.
};

