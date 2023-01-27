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
	Enemy,
	EBody,
	none,
	ECannon,
	EBulletManager,
	Camera,
	Effect,
	BackGround,
	Map,
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
	ObjectTag::Enemy,
	ObjectTag::EBody,
	ObjectTag::none,
	ObjectTag::ECannon,
	ObjectTag::EBulletManager,
	ObjectTag::Camera,
	ObjectTag::Effect,
	ObjectTag::BackGround,
	ObjectTag::Map,
};