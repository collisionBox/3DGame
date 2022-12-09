#pragma once
#include <vector>

enum class ObjectTag : unsigned char
{
	Player,
	PlayerBullet,
	Enemy,
	Camera,
	Effect,
	BackGround,
};

constexpr static ObjectTag ObjectTagAll[] =
{
	ObjectTag::Player,
	ObjectTag::PlayerBullet,
	ObjectTag::Enemy,
	ObjectTag::Camera,
	ObjectTag::Effect,
	ObjectTag::BackGround,
};