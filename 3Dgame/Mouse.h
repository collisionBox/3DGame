#pragma once
#include "DxLib.h"
typedef struct VECTOR2
{
	float x;
	float y;
};
class Mouse
{
public:
	Mouse();

	void Update();
	const float GetPosX() const { return pos.x; }
	const float GetPosY() const { return pos.y; }

private:
	VECTOR2 pos;
};

