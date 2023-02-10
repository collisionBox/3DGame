#pragma once
#include "foundation.h"
class HPGauge
{
public:
	HPGauge(float maxHP);
	static void Initialize(float maxHP);
	void Update(VECTOR& pos, float& HP, float deltaTime);
	void Draw();
private:
	VECTOR screenPos;
	float maxHP;
	float HPRatio;// HP����.
	float width;// HP�o�[�̕�.
	float halfWidth;
	float hight;// HP�o�[�̍���.
	float halfHight;
	float valiableWidth;// HP�o�[�̉ϒ�.
};
