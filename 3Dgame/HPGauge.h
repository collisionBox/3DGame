#pragma once
#include "DxLib.h"

class HPGauge
{
public:
	HPGauge(float maxHP);
	void Initialize(float maxHP);
	void Update(VECTOR& pos, float& HP, float deltaTime);
	void Draw();
private:
	VECTOR screenPos;
	float maxHP;
	float HPRatio;// HP割合.
	float width;// HPバーの幅.
	float halfWidth;
	float hight;// HPバーの高さ.
	float halfHight;
	float valiableWidth;// HPバーの可変長.
};

