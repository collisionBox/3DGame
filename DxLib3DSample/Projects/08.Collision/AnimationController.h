//-----------------------------------------------------------------------------
// @brief アニメーションコントローラクラス
// アニメーションの登録、ループ再生などの管理
//-----------------------------------------------------------------------------
#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <DxLib.h>

namespace My3dApp
{
	class AnimationController final
	{
	public:
		AnimationController(int modelHandle);
		~AnimationController();

		int AddAnimation(std::string animFileName, float animFps = 30.0f, bool isLoop = true); // アニメーションの追加

		void AddAnimationTime(float deltaTime);       // アニメーション時間のセット
		void StartAnimation(int animID);              // アニメーションの再生開始
		void StopAnimation();                         // アニメーションの再生をストップ
		bool IsPlaying();                             // 現在再生中か

		// アニメーションデータ用構造体 アニメーション1個分
		struct AnimData
		{
		public:
			AnimData();
			int   mAnimationHandle;                   // アニメーションハンドル
			int   mAnimationIndex;                    // アタッチするアニメーション番号
			float mAnimationTotalTime;                // このアニメの総再生時間
			float mAnimationPlayFps;                  // アニメーション再生速度
			bool  mIsLoopAnimation;                   // ループ再生を許可するか
		};

	private:
		int   mModelHandle;                           // 大元のモデルハンドル。これにアニメーションを取り付ける
		std::vector<AnimData> mAnimDatas;             // アニメーション複数登録用
		int   mNowAnimTypeNum;                        // 現在再生中のアニメーションID
		int   mAttachedIndex;                         // 取付後のインデックス
		float mNowAnimTime;                           // 現在再生中のアニメーション時刻
	};

}// namespace My3dApp