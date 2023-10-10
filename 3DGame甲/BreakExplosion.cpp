#include "BreakExplosion.h"

BreakExplosion::BreakExplosion(VECTOR pos, VECTOR dir) :
	EffectBase()
{
	handle = LoadEffekseerEffect("data/effect/explosion/”š”­1.efkefc", Size);
	this->dir = dir;
	this->pos = pos;

	playingEffectHandle = PlayEffekseer3DEffect(handle);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle, this->pos.x, this->pos.y, this->pos.z);
	SetSpeedPlayingEffekseer3DEffect(playingEffectHandle, PlayEffectSpeed);

	UpdateEffekseer3D();
	finish = false;
}

BreakExplosion::~BreakExplosion()
{
	DeleteEffekseerEffect(playingEffectHandle);

}

void BreakExplosion::Update(float deltaTime)
{
	if (IsEffekseer3DEffectPlaying(playingEffectHandle) == -1)
	{
		valid = false;
		finish = true;
		DeleteEffekseerEffect(playingEffectHandle);
	}

	UpdateEffekseer3D();

}

void BreakExplosion::Play()
{
	DrawEffekseer3D_Draw(playingEffectHandle);

}
