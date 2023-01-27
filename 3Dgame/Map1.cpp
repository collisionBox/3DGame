#include "Map1.h"

Map1::Map1() :
	ObjectBase(ObjectTag::BackGround)
{
	modelHandle = MV1LoadModel("data/map/block.mv1");
	colModel = modelHandle;
	if (modelHandle == -1)
	{
		printfDx("error");
	}
	//MV1SetScale(modelHandle, VGet(0.5, 0.5, 0.5));// サイズの変更.

	MV1SetPosition(modelHandle, VGet(100.0f, 0.0f, 100.0f));
	CollisionUpdate();
}

Map1::~Map1()
{
	AssetManager::DeleteMesh(modelHandle);
}

void Map1::Update(float deltaTime)
{
}

void Map1::Draw()
{
	for (int i = 0; i < mapObjectNumZ; i++)
	{
		for (int j = 0; j < mapObjectNumX; j++)
		{
			if (map[i][j] == 0)
			{
				continue;
			}

			
		}
	}
	MV1DrawModel(modelHandle);
	DrawCollider();
}
