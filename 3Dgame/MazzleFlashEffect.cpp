#include "MazzleFlashEffect.h"
#include "EffectTag.h"
MazzleFlashEffect::MazzleFlashEffect(VECTOR pos, VECTOR dir) :
	EffectBase(EffectTag::Graphic)
{
	handle = LoadEffekseerEffect("data/effect/explosion/”š”­1.efkefc", 2.0f);
	this->dir = dir;
	this->pos = pos;
	this->pos = VAdd(this->pos, VScale(this->dir, barrelHead));// –C“ƒæ“ª‚ÉƒZƒbƒg‚·‚é‚½‚ß.
	VECTOR a = VGet(1, 0, 0);
	float dot = (a.x * this->dir.x) + (a.z * this->dir.z);
	float size[2] = { sqrtf((a.x * a.x) + (a.z * a.z)), sqrtf((this->dir.x * this->dir.x) + (this->dir.z * this->dir.z)) };

	float formedAngle = dot / (size[0], size[1]);
	float theta = acosf(formedAngle);
	playingEffectHandle = PlayEffekseer3DEffect(handle);
	SetSpeedPlayingEffekseer2DEffect(playingEffectHandle, 1000);
	SetPosPlayingEffekseer3DEffect(playingEffectHandle,this->pos.x, 0, this->pos.z);
	SetRotationPlayingEffekseer3DEffect(playingEffectHandle, formedAngle, 0, sinf(theta));
	
	UpdateEffekseer3D();

}

MazzleFlashEffect::~MazzleFlashEffect()
{
	DeleteEffekseerEffect(playingEffectHandle);
}

void MazzleFlashEffect::Update(float deltaTime)
{
	//
	if (IsEffekseer3DEffectPlaying(playingEffectHandle) == -1)
	{
		valid = false;
		DeleteEffekseerEffect(playingEffectHandle);
	}

	UpdateEffekseer3D();

}

void MazzleFlashEffect::Draw()
{
	DrawEffekseer3D_Draw(playingEffectHandle);
}


