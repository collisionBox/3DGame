#include "MapModelBlock.h"
#include "AssetManager.h"

MapModelBlock::MapModelBlock(VECTOR initPos) :
	ObjectBase(ObjectTag::BackGround)
{
	modelHandle = AssetManager::GetMesh("data/map/block.mv1");
	MV1SetScale(modelHandle, VGet(1.0f, 0.2f, 1.0f));// サイズを100*100にする.
	colModel = modelHandle;
	pos = initPos;
	MV1SetPosition(modelHandle, pos);
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
	DrawCollider();
}
