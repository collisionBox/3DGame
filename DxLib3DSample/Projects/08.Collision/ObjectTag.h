#pragma once
#include <vector>

namespace My3dApp
{
	// ゲーム内アクター・当たり判定の種類別タグ
	// 必要なものはBeginとEndの間に254個まで定義できる
	enum class ObjectTag : unsigned char
	{
		Player,
		PlayerBullet,
		EnemyBullet,
		Enemy,
		BackGround,
		Camera,
		Effect,
	};

	//------------------------------------------------------------------------------------
	// @brief ループ制御用。上記タグの全要素を記述しておくこと.
	// @detail 使用法として,for( ObjectTag &tag : ObjectTagAll ) とすることで、
	// 全Tag要素のループにできる
	//------------------------------------------------------------------------------------
	constexpr static ObjectTag ObjectTagAll[] =
	{
		ObjectTag::Player,
		ObjectTag::PlayerBullet,
		ObjectTag::EnemyBullet,
		ObjectTag::Enemy,
		ObjectTag::BackGround,
		ObjectTag::Camera,
		ObjectTag::Effect
	};
}// namespace My3dApp