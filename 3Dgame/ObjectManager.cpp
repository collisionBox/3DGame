#include "ObjectManager.h"

ObjectManager* ObjectManager::Instance = nullptr;

ObjectManager::ObjectManager()
	:objects()
{
	Instance = nullptr;
}

ObjectManager::~ObjectManager()
{
	ReleseAllObj();
}

void ObjectManager::Initialize()
{
	if (!Instance)
	{
		Instance = new ObjectManager;
	}
}

void ObjectManager::Entry(ObjectBase* newObj)
{
	Instance->pendingObjects.push_back(newObj);
}

void ObjectManager::Relese(ObjectBase* releseObj)
{
	auto iter = std::find(Instance->pendingObjects.begin(), Instance->pendingObjects.end(), releseObj);
	if (iter != Instance->pendingObjects.end())
	{
		std::iter_swap(iter, Instance->pendingObjects.end() - 1);
		Instance->pendingObjects.pop_back();
		return;
	}

	ObjectTag tag = releseObj->GetTag();

	iter = std::find(Instance->objects[tag].begin(), Instance->objects[tag].end(), releseObj);
	if (iter != Instance->objects[tag].end())
	{
		std::iter_swap(iter, Instance->objects[tag].end() - 1);
		delete Instance->objects[tag].back();
	}
}

void ObjectManager::ReleseAllObj()
{
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

void ObjectManager::Update(float deltaTime)
{
	for (auto& tag : ObjectTagAll)
	{
		for (int i = 0; i < Instance->objects[tag].size(); ++i)
		{
			Instance->objects[tag][i]->Update(deltaTime);
		}
	}

	for (auto pending : Instance->pendingObjects)
	{
		ObjectTag tag = pending->GetTag();
		Instance->objects[tag].emplace_back(pending);
	}
	Instance->pendingObjects.clear();

	std::vector<ObjectBase*> deadObject;
	for (auto& tag : ObjectTagAll)
	{
		for (int i = 0; i < Instance->objects[tag].size(); ++i)
		{
			if (!Instance->objects[tag][i]->GetAlive())
			{
				deadObject.emplace_back(Instance->objects[tag][i]);
			}
		}
	}

	for (auto deadObj : deadObject)
	{
		delete deadObj;
	}
	deadObject.clear();
}

void ObjectManager::Draw()
{
	for (auto& tag : ObjectTagAll)
	{
		for (int i = 0; i < Instance->objects[tag].size(); ++i)
		{
			// 描画可能なオブジェクトのみ描画.
			if (Instance->objects[tag][i]->GetVidible())
			{
				Instance->objects[tag][i]->Draw();
			}
		}
	}
}

void ObjectManager::Collition()
{
}

ObjectBase* ObjectManager::GetFirstObject(ObjectTag tag)
{
	if (Instance->objects[tag].size() == 0)
	{
		return nullptr;
	}
	return Instance->objects[tag][0];
}

void ObjectManager::Finalize()
{
	ReleseAllObj();
	if (Instance)
	{
		delete Instance;
		Instance = nullptr;
	}
}


