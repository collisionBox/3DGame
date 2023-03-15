#pragma once
#include "foundation.h"
#include "SystemVariable.h"
#include "EffectBase.h"
#include "EffectManager.h"

class SparkEffect :
	public EffectBase
{
public:
	SparkEffect(VECTOR initPos);
	void Update();
	void Draw();
	bool GetValid();// —LŒø‚©‚Ç‚¤‚©‚ğæ“¾.
private:
	VECTOR mobility;// ˆÚ“®—Í.
	int weight;// d‚³.
	int bright;// –¾‚é‚³.
	const int downBright = 2;
};

