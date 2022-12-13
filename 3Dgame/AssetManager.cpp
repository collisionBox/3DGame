#include "AssetManager.h"
#include <string>

AssetManager* AssetManager::instance = nullptr;

AssetManager::AssetManager()
{
	instance = nullptr;
}

AssetManager::~AssetManager()
{
	instance->DeleteAllAsset();
	instance = nullptr;
}

void AssetManager::Initalize()
{
	if (!instance)
	{
		instance = new AssetManager;
	}
}

int AssetManager::GetMesh(std::string meshFileName)
{
	int meshID = 0;
	// �A�z�z�񂩂�ȑO�o�^����Ă��Ȃ������ׂ�.
	auto iter = instance->meshMap.find(meshFileName);

	// ������Ȃ���Γo�^
	if (iter == instance->meshMap.end())
	{
		meshID = MV1LoadModel(meshFileName.c_str());
		if (meshID == -1)
		{
			return meshID;
		}
		instance->meshMap.emplace(meshFileName, meshID);
	}

	meshID = MV1DuplicateModel(instance->meshMap[meshFileName]);
	instance->duplicateMesh.push_back(meshID);
	return meshID;
	

}

void AssetManager::DeleteMesh(int meshID)
{
	// Duplicate�̒��Ń��b�V�����������A�폜.
	auto iter = std::find(instance->duplicateMesh.begin(), instance->duplicateMesh.end(), meshID);
	if (iter == instance->duplicateMesh.end())
	{
		// ������.
		return;
	}

	MV1DeleteModel(meshID);

	// �����̃f�[�^�Ɠ���ւ��Ė������폜.
	std::iter_swap(iter, instance->duplicateMesh.end() - 1);
	instance->duplicateMesh.pop_back();
}

void AssetManager::DeleteAllAsset()
{
	for (auto iter = instance->meshMap.begin(); iter != instance->meshMap.end(); ++iter)
	{
		MV1DeleteModel(iter->second);
	}
	for (auto iter = instance->duplicateMesh.begin(); iter != instance->duplicateMesh.end(); ++iter)
	{
		MV1DeleteModel(*iter);
	}

	instance->meshMap.clear();
	instance->duplicateMesh.clear();

}

void AssetManager::Finalize()
{
	DeleteAllAsset();
	if (instance)
	{
		delete instance;
	}
}


