#include "HPGauge.h"

HPGauge::HPGauge(float maxHP)
{
	this->maxHP = maxHP;
}

void HPGauge::Initialize(float maxHP)
{
	this->maxHP = maxHP;
}

void HPGauge::Update(VECTOR& pos, float& HP, float deltaTime)
{
	screenPos = ConvWorldPosToScreenPos(pos);
	screenPos = VAdd(screenPos, VGet(0.0f, -50.0f, 0.0f));
	float max = screenPos.x + Width / 2;
	float min = screenPos.x - Width / 2;
	HPRatio = HP / maxHP;
	valiableWidth = min + (max - min) * HPRatio;
}
void HPGauge::Draw()
{
	DrawBoxAA(screenPos.x - Width / 2, screenPos.y - Hight / 2, screenPos.x + Width / 2, screenPos.y + Hight / 2, GetColor(255, 255, 255), false);// ƒQ[ƒW˜g
	if (HPRatio > 0)
	{
		DrawBoxAA(screenPos.x - Width / 2, screenPos.y - Hight / 2, valiableWidth, screenPos.y + Hight / 2, GetColor(255, 255, 255), true);

	}

}
