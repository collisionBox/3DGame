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
	Camera,
	Effect,
	BackGround,
};

constexpr static ObjectTag ObjectTagAll[] =
{
	ObjectTag::Player,
	ObjectTag::Body,
	ObjectTag::Cannon,
	ObjectTag::BulletManager,
	ObjectTag::Bullet,
	ObjectTag::Enemy,
	ObjectTag::Camera,
	ObjectTag::Effect,
	ObjectTag::BackGround,
};