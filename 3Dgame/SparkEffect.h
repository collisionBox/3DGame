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
	void Update(float deltaTime);
	void Draw();
	bool GetValid();// 有効かどうかを取得.
private:
	VECTOR mobility;// 移動力.
	int weight;// 重さ.
	int bright;// 明るさ.
	const int downBright = 2;
};

