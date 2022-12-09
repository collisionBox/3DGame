//-----------------------------------------------------------------------------
// @brief アセットマネージャクラス
// メッシュファイル・アニメーションの管理を行う。複数回mv1ファイルを読み込みしようとした
// 場合、クローンを作成し、ファイル読み込みを抑制する.
//-----------------------------------------------------------------------------
#pragma once
#include <string>
#include <unordered_map>
#include <atlstr.h>
#include <DxLib.h>

namespace My3dApp
{
	class AssetManager final
	{
	public:
		static void Initialize();                                   // アセットマネージャの初期化
		static int  GetMesh(std::string meshFileName);              // メッシュ（モデル）の取得
		static int  GetAnimation(std::string animationFileName);    // アニメーションの取得
		static void ReleaseMesh(int meshID);                        // メッシュ（モデル）の削除
		static void ReleaseAllAsset();                              // 全メッシュ・アニメーションの削除
		static void Finalize();                                     // アセットマネージャの終了処理

	private:
		AssetManager();
		~AssetManager();
		static AssetManager* mpInstance;                    // AssetManagerインスタンスへのポインタ（アプリ中に唯一存在する）

		std::unordered_map<std::string, int> mMeshMap;      // メッシュ原本（こちらは原本として保存だけ行い、Duplicateされたものを返す）
		std::unordered_map<std::string, int> mAnimationMap; // アニメーション原本（こちらは返す)
		std::vector<int> mDuplicatesMesh;                   // メッシュをコピーしたもの（こちらを使用する）
	};

}// namespace My3dApp