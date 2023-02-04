#include "ObjectManager.h"

// GameObjectManager実体へのポインタ定義.
ObjectManager* ObjectManager::Instance = nullptr;

//------------------------------------------------------------------------------
// @brief オブジェクトマネージャ　コンストラクタ.
//------------------------------------------------------------------------------
ObjectManager::ObjectManager()
	:objects()
{
	Instance = nullptr;
}
//------------------------------------------------------------------------------
// @brief オブジェクトマネージャ　デストラクタ.
//------------------------------------------------------------------------------
ObjectManager::~ObjectManager()
{
	ReleseAllObj();
}
//------------------------------------------------------------------------------
// @brief ゲームオブジェクトマネージャの初期化関数.
// ゲームオブジェクトマネージャを初期化する。この関数以降、ほかの関数が
// 使用できるようになる。そのため他の関数使用前にCreateを呼び出す必要がある。
//------------------------------------------------------------------------------
void ObjectManager::Initialize()
{
	if (!Instance)
	{
		Instance = new ObjectManager;
	}
}

//------------------------------------------------------------------------------
// @brief GameObject をGameObjectマネージャに追加.
// @param[in] newObj 新規作成ゲームオブジェクト.
// @detail 新規ゲームオブジェクトをマネージャーに追加する。内部で一時保管された後、
// Update()内でタグ種類毎に分類され管理される.
//------------------------------------------------------------------------------
void ObjectManager::Entry(ObjectBase* newObj)
{
	// ペンディング(未解決)オブジェクトに一時保存.
	Instance->pendingObjects.push_back(newObj);
}

//------------------------------------------------------------------------------
// @brief GameObject をマネージャから削除.
// @param[in] releaseObj 削除したいオブジェクトのポインタ.
// @detail 削除したいオブジェクトのポインタをマネージャ内で検索し削除する.
//------------------------------------------------------------------------------
void ObjectManager::Relese(ObjectBase* releseObj)
{
	// ペンディングオブジェクト内から検索.
	auto iter = std::find(Instance->pendingObjects.begin(), Instance->pendingObjects.end(), releseObj);
	if (iter != Instance->pendingObjects.end())
	{
		// 見つけたオブジェクトを最後尾に移動してデータを消す.
		std::iter_swap(iter, Instance->pendingObjects.end() - 1);
		Instance->pendingObjects.pop_back();
		return;
	}
	// 解放オブジェクトのタグ種類を得る.
	ObjectTag tag = releseObj->GetTag();

	// アクティブオブジェクト内から削除Objectを検索.
	iter = std::find(Instance->objects[tag].begin(), Instance->objects[tag].end(), releseObj);
	if (iter != Instance->objects[tag].end())
	{
		// 見つけたオブジェクトを末尾に移動し、削除.
		std::iter_swap(iter, Instance->objects[tag].end() - 1);
		delete Instance->objects[tag].back();
	}
}

//-------------------------------------------------------------------------------
// @brief 全オブジェクト削除.
//-------------------------------------------------------------------------------
void ObjectManager::ReleseAllObj()
{
	// 末尾からペンディングオブジェクトをすべてを削除
	while (!Instance->pendingObjects.empty())
	{

		delete Instance->pendingObjects.back();
		Instance->pendingObjects.pop_back();
	}

	// すべてのアクティブオブジェクトを削除
	for (auto& tag : ObjectTagAll)
	{
		// 末尾から削除
		while (!Instance->objects[tag].empty())
		{
			delete Instance->objects[tag].back();
			Instance->objects[tag].pop_back();
		}
	}
}

//-------------------------------------------------------------------------------
// @brief 全オブジェクトの更新処理.
// @param[in] 1フレームの更新時間.
// 
// @detail 全オブジェクトのUpdateメソッドを呼んだあと、
// 新規Objectをアクティブリストに追加
// 死亡Objectをアクティブリストから削除
//-------------------------------------------------------------------------------
void ObjectManager::Update(float deltaTime)
{
	// すべてのアクターの更新
	for (auto& tag : ObjectTagAll)
	{
		// 該当タグにあるすべてのオブジェクトを更新
		for (int i = 0; i < Instance->objects[tag].size(); ++i)
		{
 			Instance->objects[tag][i]->Update(deltaTime);
		}
	}
	// ペンディング中のオブジェクトをアクティブリストに追加
	for (auto pending : Instance->pendingObjects)
	{
		ObjectTag tag = pending->GetTag();
		Instance->objects[tag].emplace_back(pending);
	}
	Instance->pendingObjects.clear();

	// すべてのアクター中で死んでいるアクターをdeadObjectへ一時保管
	std::vector<ObjectBase*> deadObject;
	for (auto& tag : ObjectTagAll)
	{

		//deadObjectに移動
		for (auto obj : Instance->objects[tag])
		{
			if (!obj->GetAlive())
			{
				deadObject.emplace_back(obj);
			}
		}
		Instance->objects[tag].erase(std::remove_if(std::begin(Instance->objects[tag]), std::end(Instance->objects[tag]), [](ObjectBase* b) { return !b->GetAlive(); }), std::cend(Instance->objects[tag]));

		//// タグ内をすべて回り、死亡Objectを検索し、deadObjectsへ
		//for (int i = 0; i < Instance->objects[tag].size(); ++i)
		//{
		//	if (!Instance->objects[tag][i]->GetAlive())
		//	{
		//		deadObject.emplace_back(Instance->objects[tag][i]);
		//	}
		//}
	}

	// 死んでいるオブジェクトをdelete
	while (!deadObject.empty())
	{
		delete deadObject.back();
		deadObject.pop_back();
	}
}

//-------------------------------------------------------------------------------
// @brief 全オブジェクトの描画処理.
//-------------------------------------------------------------------------------
void ObjectManager::Draw()
{
	for (auto& tag : ObjectTagAll)
	{
		for (int i = 0; i < Instance->objects[tag].size(); ++i)
		{
			// 描画可能なオブジェクトのみ描画.
			if (Instance->objects[tag][i]->GetVisible())
			{
				
				Instance->objects[tag][i]->Draw();
			}
		}
	}
}

//-------------------------------------------------------------------------------
// @brief 全オブジェクトの当たり判定.
//-------------------------------------------------------------------------------
void ObjectManager::Collition()
{
	// プレイヤー.
	for (int playerNum = 0; playerNum < Instance->objects[ObjectTag::Player].size(); ++playerNum)
	{
		// VS弾.
		for (int bulletNum = 0; bulletNum < Instance->objects[ObjectTag::Bullet].size(); ++bulletNum)
		{
			Instance->objects[ObjectTag::Player][playerNum]->
				OnCollisionEnter(Instance->objects[ObjectTag::Bullet][bulletNum]);

			Instance->objects[ObjectTag::Bullet][bulletNum]->
				OnCollisionEnter(Instance->objects[ObjectTag::Player][playerNum]);
		}

		// VS背景.
		for (int bgNum = 0; bgNum < Instance->objects[ObjectTag::BackGround].size(); bgNum++)
		{
			Instance->objects[ObjectTag::Player][playerNum]->
				OnCollisionEnter(Instance->objects[ObjectTag::BackGround][bgNum]);
		}
	}

	// エネミー.
	for (int enemyNum = 0; enemyNum < Instance->objects[ObjectTag::Enemy].size(); ++enemyNum)
	{
		//VS弾.
		for (int bulletNum = 0; bulletNum < Instance->objects[ObjectTag::Bullet].size(); ++bulletNum)
		{
			Instance->objects[ObjectTag::Enemy][enemyNum]->
				OnCollisionEnter(Instance->objects[ObjectTag::Bullet][bulletNum]);

			Instance->objects[ObjectTag::Bullet][bulletNum]->
				OnCollisionEnter(Instance->objects[ObjectTag::Enemy][enemyNum]);
		}

		// VS背景.
		for (int bgNum = 0; bgNum < Instance->objects[ObjectTag::BackGround].size(); bgNum++)
		{
			Instance->objects[ObjectTag::Enemy][enemyNum]->
				OnCollisionEnter(Instance->objects[ObjectTag::BackGround][bgNum]);
		}
	}

	// 背景.
	for (int bgNum = 0; bgNum < Instance->objects[ObjectTag::BackGround].size(); bgNum++)
	{
		// VS弾.
		for (int bulletNum = 0; bulletNum < Instance->objects[ObjectTag::Bullet].size(); ++bulletNum)
		{
			Instance->objects[ObjectTag::Bullet][bulletNum]->
				OnCollisionEnter(Instance->objects[ObjectTag::BackGround][bgNum]);
		}
	}
	
}

//-------------------------------------------------------------------------------
// @brief タグ種類の初めのオブジェクトを返す.
// @param[in] tag ObjectTag種類
//-------------------------------------------------------------------------------
ObjectBase* ObjectManager::GetFirstObject(ObjectTag tag)
{
	if (Instance->objects[tag].size() == 0)
	{
		return nullptr;
	}
	return Instance->objects[tag][0];
}

//-------------------------------------------------------------------------------
// @brief  GameObjectManagerの後始末処理.
// @detail アプリケーション終了前に呼び出す必要がある。マネージャが確保した領域と
// マネージャ自身の解放処理を行う。Endを行わずに終了した場合はメモリリークを起こす。
// また、この関数以降はすべてのGameObjectManagerの関数は使用することはできない。
//-------------------------------------------------------------------------------
void ObjectManager::Finalize()
{
	ReleseAllObj();
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}
}


