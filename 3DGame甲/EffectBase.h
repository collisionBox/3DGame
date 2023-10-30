#pragma once
#include "DxLib.h"
#include "EffekseerForDXLib.h"

class EffectBase
{
public:
	EffectBase();

	virtual void Update(float deltaTime) = 0;
	virtual void Play() {};

	bool GetValid() const { return valid; }
protected:
	int handle;
	bool valid;// —LŒø‚©‚Ç‚¤‚©.
	VECTOR pos;
	VECTOR dir;
	int playingEffectHandle;// Ä¶’†‚Ìƒnƒ“ƒhƒ‹.



};

