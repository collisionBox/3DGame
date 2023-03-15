#pragma once
#include	 "DxLib.h"

class EffectBase
{
public:
	EffectBase();
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() {};

	bool GetValid() const { return valid; }
protected:
	VECTOR pos;
	bool valid;// —LŒø‚©‚Ç‚¤‚©.

};

