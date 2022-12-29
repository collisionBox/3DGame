#pragma once
#include <vector>

enum class ObjectTag : unsigned char
{
	Player,
	Cannon,
	PlayerBullet,
	Enemy,
	Camera,
	Effect,
	BackGround,
};

constexpr static ObjectTag ObjectTagAll[] =
{
	ObjectTag::Player,
	ObjectTag::Cannon,
	ObjectTag::PlayerBullet,
	ObjectTag::Enemy,
	ObjectTag::Camera,
	ObjectTag::Effect,
	ObjectTag::BackGround,
};