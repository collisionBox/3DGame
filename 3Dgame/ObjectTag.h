#pragma once
#include <vector>

enum class ObjectTag : unsigned char
{
	Player,
	Body,
	Cannon,
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
	ObjectTag::Body,
	ObjectTag::Cannon,
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