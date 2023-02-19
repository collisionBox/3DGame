#pragma once
#include "foundation.h"
#include "PlayerCannon.h"
#include "HPGauge.h"
class PlayerBody :
	public ObjectBase
{
public:
	PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, PlayerTag myTag, const char* failName);
	~PlayerBody();

	//static PlayerBody& Instance() { static PlayerBody body; return body; }

	void Update(float deltaTime) override;// 更新.
	void Draw() override;// 描画.
	void OnCollisionEnter(const ObjectBase* other) override;

	const PlayerTag GetPlayerTag() const { return playerTag; }

private:
	void Input(float deltaTime);
	void Rotate();


	VECTOR aimDir;// 目標方向.
	VECTOR velocity;// 加速ベクトル.
	VECTOR prevPos; // 予測ポジション.
	bool rotateNow;// 回転しているかどうか.
	float deltaWaitTime;
	float accel;
	PlayerTag playerTag;

	// コントローラー変数.
	int padInput;
	XINPUT_STATE pad;

	class PlayerCannon* cannon;
	class HPGauge* hpGauge;

	// 静的関数.
	static const float Accel;// 前進加速度.
	static const float Back;// .後退加速度
	static const float MaxSpeed;// 最大前進速度.
	static const float MinSpeed;// 最大更新速度.
	static const float OnShootingDownWaitTime;// 被撃墜時待機時間.
	const float DefaultDecel = 0.97f;// なにもしない時の減速.
	const float GripDecel = -5.0f;// グリップの減速.
	const float TurnPerformance = 5.0f;// 旋回性能.

};

