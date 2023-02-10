#include "HPGauge.h"

HPGauge::HPGauge(float maxHP)
{
	this->maxHP = maxHP;
}

void HPGauge::Initialize(float maxHP)
{
	maxHP = maxHP;
}

void HPGauge::Update(VECTOR& pos, float& HP, float deltaTime)
{
	screenPos = ConvWorldPosToScreenPos(pos);
	screenPos = VAdd(screenPos, VGet(0.0f, -50.0f, 0.0f));
	width = 40.0f;
	halfWidth = width / 2;
	hight = 10.0f;
	halfHight = hight / 2;
	float max = screenPos.x + halfWidth;
	float min = screenPos.x - halfWidth;
	HPRatio = HP / maxHP;
	valiableWidth = min + (max - min) * HPRatio;
}
void HPGauge::Draw()
{
	DrawBoxAA(screenPos.x - halfWidth, screenPos.y - halfHight, screenPos.x + halfWidth, screenPos.y + halfHight, GetColor(255, 255, 255), false);// ƒQ[ƒW˜g
	if (HPRatio > 0)
	{
		DrawBoxAA(screenPos.x - halfWidth, screenPos.y - halfHight, valiableWidth, screenPos.y + halfHight, GetColor(255, 255, 255), true);

	}

}
