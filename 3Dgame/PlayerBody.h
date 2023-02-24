#pragma once
#include "foundation.h"
#include "PlayerCannon.h"
#include "HPGauge.h"
class PlayerBody :
	public ObjectBase
{
public:
	PlayerBody(VECTOR initPos, VECTOR initDir, int inputState, ObjectTag myTag, const char* failName);
	~PlayerBody();

	//static PlayerBody& Instance() { static PlayerBody body; return body; }

	void Update(float deltaTime) override;// 更新.
	void Draw() override;// 描画.
	void OnCollisionEnter(const ObjectBase* other) override;

	void Initialize();

private:
	void Input(float deltaTime);
	void Rotate();

	VECTOR initPos;// 初期ポジション.
	VECTOR initDir;// 初期ディレクション.
	VECTOR aimDir;// 目標方向.
	VECTOR velocity;// 加速ベクトル.
	VECTOR prevPos; // 予測ポジション.
	bool rotateNow;// 回転しているかどうか.
	float deltaWaitTime;// 待機時間.
	float accel;// 加速変数.
	const float maxHP = 100.0f;
	// コントローラー変数.
	int padInput;
	XINPUT_STATE pad;

	class PlayerCannon* cannon;
	class HPGauge* hpGauge;

	const float Accel = 6.0f;// 通常の加速.
	const float Back = 5.0f;// 後退速度.
	const float MaxSpeed = 300.0f;// 最高前進速度.
	const float MinSpeed = -200.0f;// 最高後退速度.
	const float DefaultDecel = 0.97f;// なにもしない時の減速.
	const float GripDecel = -5.0f;// グリップの減速.
	const float TurnPerformance = 5.0f;// 旋回性能.
	const float OnShootingDownWaitTime = 5.0f;// 被撃墜時待機時間.
};

