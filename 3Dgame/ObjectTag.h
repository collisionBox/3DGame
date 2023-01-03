#pragma once
#include <vector>

enum class ObjectTag : unsigned char
{
	Player,
	Body,
	Cannon,
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
	ObjectTag::Bullet,
	ObjectTag::Enemy,
	ObjectTag::Camera,
	ObjectTag::Effect,
	ObjectTag::BackGround,
};