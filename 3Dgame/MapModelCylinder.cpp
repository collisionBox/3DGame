#include "MapModelCylinder.h"
#include "AssetManager.h"

MapModelCylinder::MapModelCylinder(VECTOR initPos):
	ObjectBase(ObjectTag::BackGround)
{
	const VECTOR setScale = VGet(0.24f, 0.3f, 0.24f);
	modelHandle = AssetManager::GetMesh("data/map/cylinder.mv1");
	MV1SetScale(modelHandle, setScale);// サイズを100*100にする.
	colModel = modelHandle;
	pos = initPos;
	MV1SetPosition(modelHandle, initPos);
	CollisionUpdate();
}

MapModelCylinder::~MapModelCylinder()
{
	AssetManager::DeleteMesh(modelHandle);
}

void MapModelCylinder::Update(float deltaTime)
{
}

void MapModelCylinder::Draw()
{
	MV1DrawModel(modelHandle);
}
