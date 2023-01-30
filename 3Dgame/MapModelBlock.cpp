#include "MapModelBlock.h"

MapModelBlock::MapModelBlock() :
	ObjectBase(ObjectTag::BackGround)
{
	modelHandle = MV1LoadModel("data/map/block.mv1");
	MV1SetScale(modelHandle, VGet(0.5f, 0.5f, 0.5f));
	colModel = modelHandle;

	MV1SetPosition(modelHandle, VGet(100.0f, 0.0f, 100.0f));
	CollisionUpdate();
}

MapModelBlock::~MapModelBlock()
{
	AssetManager::DeleteMesh(modelHandle);
}

void MapModelBlock::Update(float deltaTime)
{
	
}

void MapModelBlock::Draw()
{
	MV1DrawModel(modelHandle);
}
