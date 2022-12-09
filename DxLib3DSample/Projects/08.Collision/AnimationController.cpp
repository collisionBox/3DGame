#include "AnimationController.h"
#include "AssetManager.h"

namespace My3dApp
{
	//-----------------------------------------------------------------------------
	// @brief  コンストラクタ.
	// @param[in] modelHandle アニメーションを適用するモデルハンドル.
	//-----------------------------------------------------------------------------

	AnimationController::AnimationController(int modelHandle)
		: mModelHandle(modelHandle)
		, mNowAnimTypeNum(-1)
		, mNowAnimTime(0.0f)
		, mAttachedIndex(0)
	{
	}

	//-----------------------------------------------------------------------------
	// @brief  デストラクタ.
	//-----------------------------------------------------------------------------
	AnimationController::~AnimationController()
	{
	}
	//-----------------------------------------------------------------------------
	// @brief  アニメーションの追加.
	// @param[in] animFileName 追加したいアニメーションファイル名.
	// @param[in] animFPS アニメーションの再生速度（省略可。デフォルトで30fps).
	// @param[in] isLoop ループアニメーションさせるか（省略可。デフォルトはループさせる).
	// @return int アニメーション再生用ID.
	// 
	// @details コンストラクタで指定したmodelHandleのモデルに対し、アニメーションを追加する。
	// アニメーションが追加できた時はアニメーション再生IDを返す。失敗時は-1を返す.         
	//-----------------------------------------------------------------------------
	int AnimationController::AddAnimation(std::string animFileName, float animFps, bool isLoop)
	{
		AnimData anim;
		anim.mAnimationPlayFps = animFps;
		anim.mIsLoopAnimation = isLoop;

		// アニメーションデータ読み込み
		anim.mAnimationHandle = AssetManager::GetAnimation(animFileName.c_str());
		if (anim.mAnimationHandle == -1)
		{
			return -1;
		}
		anim.mAnimationIndex = MV1GetAnimNum(anim.mAnimationHandle) - 1;

		mAttachedIndex = MV1AttachAnim(mModelHandle, anim.mAnimationIndex, anim.mAnimationHandle, TRUE);
		anim.mAnimationTotalTime = MV1GetAnimTotalTime(anim.mAnimationHandle, anim.mAnimationIndex);

		// アニメーション解除
		int test;
		test = MV1DetachAnim(mModelHandle, mAttachedIndex);

		// 末尾にアニメーションデータ追加
		mAnimDatas.push_back(anim);

		// vectorに入る添え字番号返す
		return static_cast<int>(mAnimDatas.size() - 1);
	}

	//-----------------------------------------------------------------------------
	// @brief  アニメーションの増分時刻を設定.
	// @param[in] deltaTime 1フレームの増分時刻。秒単位.
	//
	// @details StartAnimationで設定されたアニメーションの再生を進める。
	// 毎フレームAddAnimationTimeを呼び出す必要がある。.         
	//-----------------------------------------------------------------------------
	void AnimationController::AddAnimationTime(float deltaTime)
	{
		mNowAnimTime += deltaTime * mAnimDatas[mNowAnimTypeNum].mAnimationPlayFps;

		// ループ再生
		if (mAnimDatas[mNowAnimTypeNum].mIsLoopAnimation && mNowAnimTime > mAnimDatas[mNowAnimTypeNum].mAnimationTotalTime)
		{
			mNowAnimTime = 0.0f;
		}
		int test;
		test = MV1SetAttachAnimTime(mModelHandle, mAttachedIndex, mNowAnimTime);
	}
	//-----------------------------------------------------------------------------
	// @brief  アニメーションの再生を開始.
	// @param[in] animID アニメーションさせたいアニメーション再生IDを指定. 
	//
	// @details animIDで指定したアニメーションの再生を開始する
	// 同じアニメーションが指定された場合、はじめから再開する.
	//-----------------------------------------------------------------------------
	void AnimationController::StartAnimation(int animID)
	{
		// 以前のアニメーションと違うアニメーションがきたら一度デタッチ
		if (animID != mNowAnimTypeNum)
		{
			if (mNowAnimTypeNum != -1)
			{
				MV1DetachAnim(mModelHandle, mAttachedIndex);
			}
			// 新規アニメーションをセット
			mNowAnimTypeNum = animID;
			mAttachedIndex = MV1AttachAnim(mModelHandle, mAnimDatas[animID].mAnimationIndex, mAnimDatas[mNowAnimTypeNum].mAnimationHandle, TRUE);
		}
		mNowAnimTime = 0.0f;
		MV1SetAttachAnimTime(mModelHandle, mAttachedIndex, mNowAnimTime);
	}

	//-----------------------------------------------------------------------------
	// @brief  現在指定されているアニメーションの再生を終了.
	//
	// @details 現在指定されているアニメーションが終了時刻でストップする
	// 再生途中のポーズで止まらないことに注意。ループ再生指定のアニメーションは無視される.
	//-----------------------------------------------------------------------------
	void AnimationController::StopAnimation()
	{
		mNowAnimTime = mAnimDatas[mNowAnimTypeNum].mAnimationTotalTime;
	}

	//-----------------------------------------------------------------------------
	// @brief  現在指定されているアニメーションは再生中か？.
	// @return true : 再生中 false : 再生終了
	//
	// @details 現在指定されているアニメーションが再生中かを返す
	// ループ指定されたものは常にtrueを返す。
	//-----------------------------------------------------------------------------
	bool AnimationController::IsPlaying()
	{
		if (mAnimDatas[mNowAnimTypeNum].mIsLoopAnimation && mNowAnimTime > mAnimDatas[mNowAnimTypeNum].mAnimationTotalTime)
		{
			return false;
		}
		return true;
	}
	//-------------------------------------------------------------------------
	// @brief アニメーションデータクラス コンストラクタ
	//-------------------------------------------------------------------------
	AnimationController::AnimData::AnimData()
		: mAnimationHandle(-1)
		, mAnimationIndex(-1)
		, mAnimationTotalTime(-1.0f)
		, mAnimationPlayFps(0.0f)
		, mIsLoopAnimation(false)
	{
	}

} // namespace My3dApp