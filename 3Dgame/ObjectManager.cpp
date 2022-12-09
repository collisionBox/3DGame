#include "ObjectManager.h"

ObjectManager* ObjectManager::instance = nullptr;

ObjectManager::ObjectManager()
	:objects()
{
	instance = nullptr;
}

ObjectManager::~ObjectManager()
{
	ReleseAllObj();
}

void ObjectManager::Initialize()
{
	if (!instance)
	{
		instance = new ObjectManager;
	}
}

void ObjectManager::Entry(ObjectBase* newObj)
{
	instance->pendingObjects.push_back(newObj);
}

void ObjectManager::Relese(ObjectBase* releseObj)
{
	auto iter = std::find(instance->pendingObjects.begin(), instance->pendingObjects.end(), releseObj);
	if (iter != instance->pendingObjects.end())
	{
		std::iter_swap(iter, instance->pendingObjects.end() - 1);
		instance->pendingObjects.pop_back();
		return;
	}

	ObjectTag tag = releseObj->GetTag();

	iter = std::find(instance->objects[tag].begin(), instance->objects[tag].end(), releseObj);
	if (iter != instance->objects[tag].end())
	{
		std::iter_swap(iter, instance->objects[tag].end() - 1);
		delete instance->objects[tag].back();
	}
}

void ObjectManager::ReleseAllObj()
{
	while (!instance->pendingObjects.empty())
	{
		delete instance->pendingObjects.back();
		instance->pendingObjects.pop_back();
	}

	// すべてのアクティブオブジェクトを削除
	for (auto& tag : ObjectTagAll)
	{
		// 末尾から削除
		while (!instance->objects[tag].empty())
		{
			delete instance->objects[tag].back();
			instance->objects[tag].pop_back();
		}
	}
}

void ObjectManager::Update(float deltaTime)
{
	for (auto& tag : ObjectTagAll)
	{
		for (int i = 0; i < instance->objects[tag].size(); ++i)
		{
			instance->objects[tag][i]->Update(deltaTime);
		}
	}

	for (auto pending : instance->pendingObjects)
	{
		ObjectTag tag = pending->GetTag();
		instance->objects[tag].emplace_back(pending);
	}
	instance->pendingObjects.clear();

	std::vector<ObjectBase*> deadObject;
	for (auto& tag : ObjectTagAll)
	{
		for (int i = 0; i < instance->objects[tag].size(); ++i)
		{
			if (instance->objects[tag][i]->GetAlive())
			{
				deadObject.emplace_back(instance->objects[tag][i]);
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
		for (int i = 0; i < instance->objects[tag].size(); ++i)
		{
			if (instance->objects[tag][i]->GetVidible())
			{
				instance->objects[tag][i]->Draw();
			}
		}
	}
}

void ObjectManager::Collition()
{
}

ObjectBase* ObjectManager::GetFirstObject(ObjectTag tag)
{
	if (instance->objects[tag].size() == 0)
	{
		return nullptr;
	}
	return instance->objects[tag][0];
}

void ObjectManager::Finalize()
{
	ReleseAllObj();
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}


