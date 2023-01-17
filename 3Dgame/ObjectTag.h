#pragma once
#include <vector>

enum class ObjectTag : unsigned char
{
	Player,
	Player2,
	Body,
	Body2,
	Cannon,
	Cannon2,
	BulletManager,
	Bullet,
	Bullet2,
	Enemy,
	EBody,
	none,
	ECannon,
	EBulletManager,
	Camera,
	Effect,
	BackGround,
};

constexpr static ObjectTag ObjectTagAll[] =
{
	ObjectTag::Player,
	ObjectTag::Player2,
	ObjectTag::Body,
	ObjectTag::Body2,
	ObjectTag::Cannon,
	ObjectTag::Cannon2,
	ObjectTag::BulletManager,
	ObjectTag::Bullet,
	ObjectTag::Bullet2,
	ObjectTag::Enemy,
	ObjectTag::EBody,
	ObjectTag::none,
	ObjectTag::ECannon,
	ObjectTag::EBulletManager,
	ObjectTag::Camera,
	ObjectTag::Effect,
	ObjectTag::BackGround,
};