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
	bool GetValid();// �L�����ǂ������擾.
private:
	VECTOR mobility;// �ړ���.
	int weight;// �d��.
	int bright;// ���邳.
	const int downBright = 2;
};

