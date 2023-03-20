#include "SparkEffect.h"

SparkEffect::SparkEffect(VECTOR initPos) :
	EffectBase()
{
	pos = initPos;
	mobility = VGet(GetRand(1000) - 500, -GetRand(500), -GetRand(1000) + 500);
	weight = GetRand(10);
	bright = 255;
	valid = true;
}

void SparkEffect::Update(float deltaTime)
{
	pos = VAdd(pos, VScale(mobility, deltaTime));
	pos.y += weight;
	bright -= downBright;
}

void SparkEffect::Draw()
{
	DrawPixel3D(VScale(pos, 100), GetColor(bright, bright, bright));
}

bool SparkEffect::GetValid()
{
	if (bright == 0)
	{
		return true;
	}
	return false;
}
