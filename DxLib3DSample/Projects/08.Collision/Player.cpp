//-----------------------------------------------------------------------------
// @brief  プレイヤークラス.
//-----------------------------------------------------------------------------
#include "Player.h"
#include "AssetManager.h"
#include "AnimationController.h"
#include "math3D.h"

namespace My3dApp 
{
	//-----------------------------------------------------------------------------
	// @brief  コンストラクタ.
	//-----------------------------------------------------------------------------
	Player::Player()
		: GameObject(ObjectTag::Player)
		, mAnimControl(nullptr)
		, mAnimTypeId(0)
		, mRotateNow(false)
	{
		mVelocity = VGet(0, 0, 0);

		// ３Ｄモデルの読み込み
		mModelHandle = AssetManager::GetMesh("data/model/player2/unityChanModel.mv1");
		MV1SetScale(mModelHandle, VGet(0.01f, 0.01f, 0.01f));

		// アニメーションコントローラ
		mAnimControl = new AnimationController(mModelHandle);

		mAnimControl->AddAnimation("data/model/player2/unityChanAnimIdle.mv1");
		mAnimControl->AddAnimation("data/model/player2/unityChanAnimRun.mv1");
		mAnimControl->AddAnimation("data/model/player2/UnityChanAnimPunch.mv1");

		mAnimControl->StartAnimation(mAnimTypeId);

		mPos = VGet(0, 0, 0);
		mDir = VGet(1, 0, 0);
		mAimDir = mDir;

		// 当たり判定球セット
		mCollisionType = CollisionType::Sphere;
		mCollisionSphere.mLocalCenter = VGet(0, 50.0, 0);
		mCollisionSphere.mRadius = 30.0f;
		
		//足元当たり判定線分セット
		mCollisionLine = LineSegment(VGet(0.0f, 20.0f, 0.0f), VGet(0.0, -30.0f, 0.0f));

	}

	//-----------------------------------------------------------------------------
	// @brief  デストラクタ.
	//-----------------------------------------------------------------------------
	Player::~Player()
	{
		// モデルのアンロード.
		AssetManager::ReleaseMesh(mModelHandle); //MV1DeleteModel(modelHandle);

		delete mAnimControl;
	}

	//-----------------------------------------------------------------------------
	// @brief  更新.
	// @param[in] deltaTime １フレーム分の経過時間
	//-----------------------------------------------------------------------------
	void Player::Update(float deltaTime)
	{
		mAnimControl->AddAnimationTime(deltaTime);

		Rotate();
		Input(deltaTime);

		// 移動処理
		mPos += mVelocity;

		// ３Dモデルのポジション設定
		MV1SetPosition(mModelHandle, mPos);

		// 向きに合わせてモデルを回転.(mixamoのモデルはX軸反対向きに出るのでまずベクトルを180度回転させる
		MATRIX rotYMat = MGetRotY(180.0f * (float)(DX_PI / 180.0f));
		VECTOR negativeVec = VTransform(mDir, rotYMat);

		// モデルに回転をセットする
		MV1SetRotationZYAxis(mModelHandle, negativeVec, VGet(0.0f, 1.0f, 0.0f), 0.0f);

		//当たり判定モデルも位置更新
		CollisionUpdate();
	}

	//-----------------------------------------------------------------------------
	// @brief  描画.
	//-----------------------------------------------------------------------------
	void Player::Draw()
	{
		// ３Ｄモデルの描画
		MV1DrawModel(mModelHandle);
		DrawCollider();
	}

	//-----------------------------------------------------------------------------
	// @brief     プレイヤーが他のオブジェクトと当たった時の処理
	// @other[in] GameObject* このクラスと他のゲームオブジェクト(other)が衝突したときの処理を行う
	// @detail    プレイヤーのめり込み戻しなどのリアクション処理を記述する
	//-----------------------------------------------------------------------------
	void Player::OnCollisonEnter(const GameObject* other)
	{
		ObjectTag tag = other->GetTag();

		// 背景との衝突
		if (tag == ObjectTag::BackGround)
		{
			int colModel = other->GetCollisionModel();

			// 背景と自分の境界球との当たり判定
			MV1_COLL_RESULT_POLY_DIM colinfo;
			if (CollisionPair(mCollisionSphere, colModel, colinfo))
			{
				// 当たっている場合は押し戻し量を計算
				VECTOR pushBackVec = CalcSpherePushBackVecFromMesh(mCollisionSphere, colinfo);
				mPos += pushBackVec;
				// コリジョン情報の解放
				MV1CollResultPolyDimTerminate(colinfo);

				CollisionUpdate();
			}

			//背景と足元線分当たり判定
			MV1_COLL_RESULT_POLY colinfoLine;
			if (CollisionPair(mCollisionLine, colModel, colinfoLine))
			{
				// 当たっている場合は足元を衝突点に合わせる
				mPos = colinfoLine.HitPosition;

				CollisionUpdate();
			}
		}
	}
	//-----------------------------------------------------------------------------
	// @brief プレイヤーの入力＆移動処理
	// @param[in] deltaTime 1フレーム分の経過時間
	//-----------------------------------------------------------------------------
	void Player::Input(float deltaTime)
	{
		// キー入力取得
		int key = GetJoypadInputState(DX_INPUT_KEY_PAD1);

		// 上下左右方向
		VECTOR UP = { 0, 0, 1 };
		VECTOR DOWN = { 0, 0,-1 };
		VECTOR LEFT = { -1, 0, 0 };
		VECTOR RIGHT = { 1, 0, 0 };

		VECTOR inputVec = VGet(0, 0, 0);

		bool input = false;

		// 上を押していたら上に進む
		if (key & PAD_INPUT_UP)
		{
			inputVec = UP + inputVec;
			input = true;
		}

		// 下を押していたら下に進む
		if (key & PAD_INPUT_DOWN)
		{
			inputVec = DOWN + inputVec;
			input = true;
		}

		// 右を押していたら右に進む
		if (key & PAD_INPUT_RIGHT)
		{
			inputVec = RIGHT + inputVec;
			input = true;
		}

		// 左を押していたら左に進む
		if (key & PAD_INPUT_LEFT)
		{
			inputVec = LEFT + inputVec;
			input = true;
		}

		// 入力があったら加速・ないとき減速
		if (input)
		{
			// 左右・上下同時押しなどで入力ベクトルが０の時は無視
			if (VSquareSize(inputVec) < 0.5f)
			{
				return;
			}
			// 方向を正規化
			inputVec = VNorm(inputVec);

			// 入力方向は現在向いている向きと異なるか？
			if (IsNearAngle(inputVec, mDir))
			{
				mDir = inputVec;
			}
			else
			{
				mRotateNow = true;
				mAimDir = inputVec;
			}

			// mVelocity += inputVec * moveSpeed * deltaTime;
			mVelocity = inputVec + (inputVec * deltaTime * 200.0f);

			// もしほかのモーション中だったら走りモーションへ
			if (mAnimTypeId != 1)
			{
				mAnimTypeId = 1;
				mAnimControl->StartAnimation(mAnimTypeId);
			}
		}
		else
		{
			mVelocity *= 0.9f;
			// もしほかのモーション中だったら歩きモーションへ
			if (mAnimTypeId != 0)
			{
				mAnimTypeId = 0;
				mAnimControl->StartAnimation(mAnimTypeId);
			}
		}
	}

	//---------------------------------------------------------------------------------
	// @brief プレイヤーの回転処理
	// @detail 非公開関数。mRotateNowのフラグが立っているときに、mDirがmAimDirになるまで回転する
	//---------------------------------------------------------------------------------
	void Player::Rotate()
	{
		if (mRotateNow)
		{
			// 回転が目標角度に十分近ければ回転モード終了
			if (IsNearAngle(mAimDir, mDir))
			{
				mDir = mAimDir;
				mRotateNow = false;
			}
			else
			{
				// 回転させる
				VECTOR interPolateDir;
				interPolateDir = RotateForAimVecYAxis(mDir, mAimDir, 10.0f);

				// 回転が目標角度を超えていないか
				VECTOR cross1, cross2;
				cross1 = VCross(mDir, mAimDir);
				cross2 = VCross(interPolateDir, mAimDir);

				//目標角度を超えたら終了
				if (cross1.y * cross2.y < 0.0f)
				{
					interPolateDir = mAimDir;
					mRotateNow = false;
				}
				// 目標ベクトルに10度だけ近づけた角度
				mDir = interPolateDir;
			}
		}
	}

}// namespace My3dApp