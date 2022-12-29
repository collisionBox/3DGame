#pragma once
#include "DxLib.h"
#include <string>
#include <unordered_map>
#include <atlstr.h>

class AssetManager final
{
public:
	static void Initalize();// 初期化.
	static int GetMesh(std::string meshFileName);// メッシュ（モデル）の取得.
	static void DeleteMesh(int meshID);
	static void DeleteAllAsset();
	// メッシュ（モデル）の削除.
	static void Finalize();// アセットマネージャーの終了処理.

private:
	AssetManager();
	~AssetManager();
	static AssetManager* Instance;

	std::unordered_map<std::string, int> meshMap;// メッシュ原本.
	std::vector<int> duplicateMesh;// メッシュを複製したもの
};

