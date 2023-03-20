#pragma once
#include <vector>

enum class ObjectTag : unsigned char
{
	Player,
	Player1,
	Player2,
	Body,
	Cannon,
	BulletManager,
	Bullet,
	Camera,
	Effect,
	BackGround,
	Map,
};

constexpr static ObjectTag ObjectTagAll[] =
{
	ObjectTag::Player1,
	ObjectTag::Player2,
	ObjectTag::Body,
	ObjectTag::Cannon,
	ObjectTag::BulletManager,
	ObjectTag::Bullet,
	ObjectTag::Camera,
	ObjectTag::Effect,
	ObjectTag::BackGround,
	ObjectTag::Map,
};

enum class PlayerTag : unsigned char
{
	Player1,
	Player2,
};