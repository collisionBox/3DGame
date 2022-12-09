#include "AssetManager.h"
#include <string>

namespace My3dApp
{
	// アセットマネージャ実体へのポインタ定義
	AssetManager* AssetManager::mpInstance = nullptr;

	//-----------------------------------------------------------------------------
	// @brief  コンストラクタ.
	//-----------------------------------------------------------------------------
	AssetManager::AssetManager()
	{
		mpInstance = nullptr;
	}

	//-----------------------------------------------------------------------------
	// @brief  デストラクタ.
	//-----------------------------------------------------------------------------
	AssetManager::~AssetManager()
	{
		mpInstance->ReleaseAllAsset();
		mpInstance = nullptr;
	}
	//-----------------------------------------------------------------------------
	// @brief  アセットマネージャの生成
	// @detail dxlibInitの後にアセットマネージャを使用するための初期化処理を行う
	// Create無しに他のアセットマネージャの関数をを使用することはできない。
	//-----------------------------------------------------------------------------
	void AssetManager::Initialize()
	{
		if (!mpInstance)
		{
			mpInstance = new AssetManager;
		}
	}

	//-----------------------------------------------------------------------------
	// @brief  メッシュの取得.
	// @param[in] meshFileName 取得したいメッシュファイル名.
	// @return int メッシュのハンドル.
	// 
	// @details メッシュ（モデル)ハンドルを取得する。
	// 同じファイル名を2度以上指定したときは、ファイル読み込みは行われず、duplicateされたハンドルを返す。
	// ファイルが見つからないときは-1を返す.
	//-----------------------------------------------------------------------------
	int AssetManager::GetMesh(std::string meshFileName)
	{
		int meshId = 0;
		// 連想配列から以前に登録されてないかを調べる
		auto iter = mpInstance->mMeshMap.find(meshFileName);

		// 見つからなかった場合は新規でファイルを読み込み、連想配列に記録する
		if (iter == mpInstance->mMeshMap.end())
		{
			meshId = MV1LoadModel(meshFileName.c_str());
			if (meshId == -1)
			{
				return meshId;
			}
			mpInstance->mMeshMap.emplace(meshFileName, meshId); //mMeshMap[meshFileName] = meshIdのこと
		}

		// 新規読み込みも2回目読み込みも、duplicateしたものを返却する
		// メッシュを使うキャラクターが複数いた場合に、原本を消されると全員消えて困るため
		// メッシュのコピー削除用にmDuplicateMeshに保存
		meshId = MV1DuplicateModel(mpInstance->mMeshMap[meshFileName]);
		mpInstance->mDuplicatesMesh.push_back(meshId);
		return meshId;
	}

	//-----------------------------------------------------------------------------
	// @brief  アニメーションの読み込み.
	// @param[in] animationFileName 読み込みたいアニメーションファイル名.
	// @return int アニメーションハンドル.
	// 
	// @details アニメーションをファイル読み込みし、アニメーションハンドルを返す
	// 同じファイル名で2度以上読み込まれた場合は、読み込みを行わずハンドルのみ返す
	// アニメーションはDuplicateされない。ファイルが見つからないときは-1を返す.         
	//-----------------------------------------------------------------------------
	int AssetManager::GetAnimation(std::string animationFileName)
	{
		int animId = 0;
		auto iter = mpInstance->mAnimationMap.find(animationFileName);

		// 見つからなかった場合は新規読み込みし、連想配列に記録する
		if (iter == mpInstance->mAnimationMap.end())
		{
			animId = MV1LoadModel(animationFileName.c_str());
			if (animId == -1)
			{
				return animId;
			}
			mpInstance->mAnimationMap.emplace(animationFileName, animId);  // mAnimationMap[animationFileName] = animId;のこと
		}

		// アニメーションのIDを返す
		return mpInstance->mAnimationMap[animationFileName];
	}

	//-----------------------------------------------------------------------------
	// @brief  メッシュの解放
	// @param[in] meshID 解放したいモデルハンドル.
	// 
	// @details duplicateされたモデルハンドルを開放する
	// duplicateされたモデルハンドルなので、全部消しても原本のモデルハンドルは内部的に残る         
	//-----------------------------------------------------------------------------
	void AssetManager::ReleaseMesh(int meshID)
	{
		// Duplicateの中でメッシュを検索し、削除
		auto iter = std::find(mpInstance->mDuplicatesMesh.begin(), mpInstance->mDuplicatesMesh.end(), meshID);
		if (iter == mpInstance->mDuplicatesMesh.end())
		{
			// 見つからなかった
			return;
		}

		MV1DeleteModel(meshID);

		// 末尾のデータと入れ替えて末尾を削除
		std::iter_swap(iter, mpInstance->mDuplicatesMesh.end() - 1);
		mpInstance->mDuplicatesMesh.pop_back();
	}

	//-----------------------------------------------------------------------------
	// @brief  　すべてのメッシュの解放
	// 
	// @details duplicate, 原本のモデルハンドル、アニメーションすべてを開放する
	// アプリケーションの終了時にdxLib_End()より前に呼び出す必要がある。.
	//-----------------------------------------------------------------------------
	void AssetManager::ReleaseAllAsset()
	{
		// 全てのアニメーションを開放する
		for (auto iter = mpInstance->mAnimationMap.begin(); iter != mpInstance->mAnimationMap.end(); ++iter)
		{
			MV1DeleteModel(iter->second);

		}
		// 全てのモデルを開放する
		for (auto iter = mpInstance->mMeshMap.begin(); iter != mpInstance->mMeshMap.end(); ++iter)
		{
			MV1DeleteModel(iter->second);

		}
		// 全てのDuplicateを削除する
		for (auto iter = mpInstance->mDuplicatesMesh.begin(); iter != mpInstance->mDuplicatesMesh.end(); ++iter)
		{
			MV1DeleteModel(*iter);
		}

		mpInstance->mAnimationMap.clear();
		mpInstance->mMeshMap.clear();
		mpInstance->mDuplicatesMesh.clear();
	}
	//------------------------------------------------------------------------------------------
	// @brief  AssetManagerの後始末処理.
	// @detail アプリケーション終了前に呼び出す必要がある。マネージャが確保した領域と
	// マネージャ自身の解放処理を行う。Endを行わずに終了した場合はメモリリークを起こす。
	// またこの関数以降にAssetMangerの関数を使用することはできない。
	//------------------------------------------------------------------------------------------
	void AssetManager::Finalize()
	{	
		ReleaseAllAsset();
		if (mpInstance)
		{
			delete mpInstance;
		}
	}

} // namespace My3dApp