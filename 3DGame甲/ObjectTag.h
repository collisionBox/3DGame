#pragma once

enum class ObjectTag : unsigned char
{
	Player1,
	Player2,
	Bullet,
	Camera,
	BackGround,
};

constexpr static ObjectTag ObjectTagAll[] =
{
	ObjectTag::Player1,
	ObjectTag::Player2,
	ObjectTag::Bullet,
	ObjectTag::Camera,
	ObjectTag::BackGround,
};

